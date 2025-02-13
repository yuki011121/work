from langchain.chains import RetrievalQA
from langchain.schema.messages import HumanMessage, SystemMessage, AIMessage
from langchain.prompts import PromptTemplate

from langchain_openai import OpenAIEmbeddings, OpenAI
from langchain.text_splitter import CharacterTextSplitter, \
    RecursiveCharacterTextSplitter
from langchain_community.vectorstores import FAISS
from langchain_community.llms.chatglm3 import ChatGLM3
from langchain_community.document_loaders import UnstructuredFileLoader
from langchain_community.document_loaders import TextLoader
import gradio as gr
from langchain.vectorstores import LanceDB
import lancedb
from langchain.retrievers import BM25Retriever, EnsembleRetriever
from langchain.schema import Document
from langchain.embeddings.openai import OpenAIEmbeddings

# import os
# from dotenv import load_dotenv, find_dotenv
# load_dotenv(find_dotenv('.env'))
#
# OPENAI_API_KEY=os.environ.get("OPENAI_API_KEY")
# OPENAI_API_BASE=os.environ.get("OPENAI_API_BASE")
#
# from langchain_openai import OpenAIEmbeddings
# embedding_model = OpenAIEmbeddings(
#      openai_api_base=OPENAI_API_BASE,
#      openai_api_key=OPENAI_API_KEY,
# )
# embedding_model
from langchain_community.embeddings import HuggingFaceBgeEmbeddings
from langchain_community.vectorstores import Chroma

# import os
# os.environ["OPENAI_API_BASE"] = "https://api.openai-proxy.org/v1"
# os.environ["OPENAI_API_KEY"] = "sk-06vk1oTAEV8hS51hapAQd9aVCyrBIEST1eizwHm4FcO2CpTe"

from langchain_openai import OpenAIEmbeddings
embedding_model = OpenAIEmbeddings(
     openai_api_base="https://api.openai-proxy.org/v1",
     openai_api_key="sk-06vk1oTAEV8hS51hapAQd9aVCyrBIEST1eizwHm4FcO2CpTe",
)
# model_name = "F:/BAAIbge-base-en"
# encode_kwargs = {'normalize_embeddings': True} # set True to compute cosine similarity

# embedding_model = HuggingFaceBgeEmbeddings(
# model_name=model_name,
# model_kwargs={'device': 'cpu'},
# encode_kwargs=encode_kwargs
# )
# embedding_model

# Load docs
from langchain.vectorstores import LanceDB
import lancedb
from langchain.retrievers import BM25Retriever, EnsembleRetriever
from langchain.schema import Document
from langchain.embeddings.openai import OpenAIEmbeddings
from langchain.document_loaders import PyPDFLoader
path = "祝福(2).pdf"

# loader = TextLoader(path, encoding="GBK")
# # loader = UnstructuredFileLoader(path)
# docs = loader.load()
# # splitter = CharacterTextSplitter(chunk_size=100, chunk_overlap=30)
# splitter = RecursiveCharacterTextSplitter(chunk_size=100, chunk_overlap=30)
# chunks = splitter.split_documents(docs)
# texts_list = [text.page_content for text in chunks]
loader = PyPDFLoader(path)
pages = loader.load_and_split()
# print(chunks)

# # vectordb
#
# db = FAISS.from_documents(
#     chunks,
#     embedding_model,
# )
# db.save_local("./faiss/zhufu1")  # 持久化目录
# # db = FAISS.load_local("./faiss/zhufu1",
# #                       embedding_model,
# #                       allow_dangerous_deserialization=True)
bm25_retriever = BM25Retriever.from_documents(pages)
bm25_retriever.k =  2  # Retrieve top 2 results

db = lancedb.connect('/tmp/lancedb')
table = db.create_table("pandas_docs", data=[
    {"vector": embedding_model.embed_query("Hello World"), "text": "Hello World", "id": "1"}
], mode="overwrite")

docsearch = LanceDB.from_documents(pages, embedding_model, connection=table)
retriever_lancedb = docsearch.as_retriever(search_kwargs={"k": 2})

ensemble_retriever = EnsembleRetriever(retrievers=[bm25_retriever, retriever_lancedb],
                                       weights=[0.4, 0.6])

# query = "什么是福礼？"
# docs = ensemble_retriever.get_relevant_documents(query)
# print(docs)

# llm

# llm = OpenAI()
# messages = [
#     SystemMessage(
#         content="You are an intelligent AI assistant, named ChatGLM3."),
# ]
messages = [
    SystemMessage(
        content="你是一个叫做ChatGLM3的人工智能助手"),
]

from langchain.chat_models import ChatOpenAI
from langchain.schema.runnable import RunnablePassthrough
from langchain.schema.output_parser import StrOutputParser

llm = ChatOpenAI(model_name="gpt-3.5-turbo",
                 temperature=0,
                 openai_api_base="https://api.openai-proxy.org/v1",
                 openai_api_key="sk-06vk1oTAEV8hS51hapAQd9aVCyrBIEST1eizwHm4FcO2CpTe",
                 )

# custom prompt
qa_template = "以下为背景知识：\n{context}\n请根据以上背景知识, 回答这个问题：{question}。"

prompt = PromptTemplate(
    template=qa_template,
    input_variables=["context", "question"]
)
chain_type_kwargs = {"prompt": prompt}


# retriever = db.as_retriever(search_kwargs={"k": 1})

qa = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=ensemble_retriever,
    chain_type_kwargs=chain_type_kwargs,
)


query = "为什么婆婆要把祥林嫂再嫁出去？"

response = qa.run(query=query)
print(response)

# 定义聊天和反馈逻辑
feedback_list = []

def chat(query, history):
    response = qa.run(query)
    history.append((query, response))
    return history, response

def update_feedback(history, feedback):
    feedback_list.append(feedback)
    return history, str(feedback_list)

with gr.Blocks() as demo:
    with gr.Row():
        with gr.Column():
            chatbot = gr.Chatbot()
            msg = gr.Textbox(label="Query")
            submit = gr.Button("Send")
            feedback = gr.Slider(1, 5, step=1, label="Satisfaction", visible=False)
            submit_feedback = gr.Button("Submit Feedback", visible=False)

        with gr.Column():
            feedback_display = gr.Textbox(label="Feedback Received", interactive=False)

    def on_submit(query, history):
        history, response = chat(query, history)
        return history, gr.update(visible=True), gr.update(visible=True)

    def on_submit_feedback(history, feedback):
        history, feedbacks = update_feedback(history, feedback)
        return history, feedbacks, gr.update(visible=False), gr.update(visible=False)

    submit.click(on_submit, inputs=[msg, chatbot], outputs=[chatbot, feedback, submit_feedback])
    submit_feedback.click(on_submit_feedback, inputs=[chatbot, feedback], outputs=[chatbot, feedback_display, feedback, submit_feedback])

demo.launch(inbrowser=True)

# # #好用！但有缺陷
# feedback_list = []
#
# def chat(query, history, feedback):
#     response = qa.run(query)
#     history.append((query, response))
#     feedback_list.append(feedback)
#     return history, str(feedback_list)
#
# def get_feedback():
#     return str(feedback_list)
#
# with gr.Blocks() as demo:
#     with gr.Row():
#         with gr.Column():
#             chatbot = gr.Chatbot()
#             msg = gr.Textbox(label="Query")
#             feedback = gr.Slider(1, 5, step=1, label="Satisfaction")
#             submit = gr.Button("Send")
#
#         with gr.Column():
#             feedback_display = gr.Textbox(label="Feedback Received", interactive=False)
#
#     submit.click(chat, inputs=[msg, chatbot, feedback], outputs=[chatbot, feedback_display])
#
# demo.launch(inbrowser=True)

