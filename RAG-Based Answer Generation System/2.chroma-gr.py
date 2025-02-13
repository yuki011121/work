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

model_name = "F:/BAAIbge-base-en"
encode_kwargs = {'normalize_embeddings': True} # set True to compute cosine similarity

embedding_model = HuggingFaceBgeEmbeddings(
model_name=model_name,
model_kwargs={'device': 'cpu'},
encode_kwargs=encode_kwargs
)
embedding_model

# Load docs
path = "祝福 (1).txt"

loader = TextLoader(path, encoding="GBK")
# loader = UnstructuredFileLoader(path)
docs = loader.load()



# splitter = CharacterTextSplitter(chunk_size=100, chunk_overlap=30)
splitter = RecursiveCharacterTextSplitter(chunk_size=100, chunk_overlap=30)
chunks = splitter.split_documents(docs)
# print(chunks)

# # vectordb
#
# db = FAISS.from_documents(
#     chunks,
#     embedding_model,
# )
# db.save_local("./faiss/zhufu1")  # 持久化目录
# db = FAISS.load_local("./faiss/zhufu1",
#                       embedding_model,
#                       allow_dangerous_deserialization=True)


# 创建数据库
# db = Chroma.from_documents(chunks,embedding_model,persist_directory="VectorStore")
# db.persist()
# print("数据库创建完成~")
#调用
db = Chroma(persist_directory="VectorStore",embedding_function=embedding_model)

# llm

# llm = OpenAI()
# messages = [
#     SystemMessage(
#         content="You are an intelligent AI assistant, named ChatGLM3."),
# ]
messages = [
    SystemMessage(
        content="You are an intelligent AI assistant, named ChatGLM3."),
]

llm = ChatGLM3(
    prefix_messages=messages,
    # endpoint_url="http://219.216.64.75:31815/v1/chat/completions",
    endpoint_url="http://219.216.64.127:31827/v1/chat/completions",
    max_token=8096,
    top_p=0.9,
)

# custom prompt
qa_template = "以下为背景知识：\n{context}\n请根据以上背景知识, 回答这个问题：{question}。"

prompt = PromptTemplate(
    template=qa_template,
    input_variables=["context", "question"]
)
chain_type_kwargs = {"prompt": prompt}


retriever = db.as_retriever(search_kwargs={"k": 1})

qa = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=retriever,
    chain_type_kwargs=chain_type_kwargs,
)


query = "为什么婆婆要把祥林嫂再嫁出去？"
rel_docs = db.similarity_search(query)
# for doc in rel_docs:
#    print(doc.page_content[:50])
print(rel_docs)
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
# 实验用
# print(qa.invoke(query)['result'])
# # response = qa.run('卫老婆子是个怎样的人？')
# # print(response)
#
# # def chat(query, history):
# #     response=qa.run(query)
# #     # print(response)
# #     return response
# #
# # # chat("胶菜是什么?")
# # demo=gr.ChatInterface(chat)
# # demo.launch(inbrowser=True)
