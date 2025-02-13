from flask import Flask, request, render_template_string
from langchain.chains import RetrievalQA
from langchain.schema.messages import HumanMessage, SystemMessage, AIMessage
from langchain.prompts import PromptTemplate

from langchain_openai import OpenAIEmbeddings, OpenAI
from langchain.text_splitter import CharacterTextSplitter, RecursiveCharacterTextSplitter
from langchain_community.vectorstores import FAISS
from langchain_community.llms.chatglm3 import ChatGLM3
from langchain_community.document_loaders import UnstructuredFileLoader
from langchain_community.document_loaders import TextLoader

import os
import openai
from getpass import getpass

from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.embeddings import OpenAIEmbeddings
from langchain.document_loaders import TextLoader
from langchain.vectorstores import FAISS
from langchain.document_loaders.pdf import PyPDFLoader
from langchain.embeddings import HuggingFaceBgeEmbeddings
from langchain.chains import RetrievalQA
from langchain.chat_models import ChatOpenAI
from langchain.retrievers import ContextualCompressionRetriever
from langchain.retrievers.document_compressors import CohereRerank

import cohere

cohere_api_key = "u8y6W5xZrphMneY5hqMwMgtyidvXsnUYwez2oJSK"

embedding_model = OpenAIEmbeddings(
     openai_api_base="https://api.openai-proxy.org/v1",
     openai_api_key="sk-06vk1oTAEV8hS51hapAQd9aVCyrBIEST1eizwHm4FcO2CpTe",
)

path = "祝福(2).pdf"
loader = PyPDFLoader(path)
docs = loader.load()
pages = loader.load_and_split()

text_splitter = RecursiveCharacterTextSplitter(chunk_size=100, chunk_overlap=30)
texts = text_splitter.split_documents(docs)

from langchain.vectorstores import LanceDB
import lancedb
db = lancedb.connect('/tmp/lancedb')
table = db.create_table("pandas_docs", data=[
    {"vector": embedding_model.embed_query("Hello World"), "text": "Hello World", "id": "1"}
], mode="overwrite")

vectorstore = LanceDB.from_documents(pages, embedding_model, connection=table)
retriever = vectorstore.as_retriever(search_kwargs={"k": 2})

from langchain.retrievers import BM25Retriever
bm25_retriever = BM25Retriever.from_documents(pages)
bm25_retriever.k =  2  # Retrieve top 2 results

def pretty_print_docs(docs):
    print(
        f"\n{'-' * 100}\n".join(
            [f"Document {i+1}:\n\n" + d.page_content for i, d in enumerate(docs)]
        )
    )

# compressor = CohereRerank(cohere_api_key=cohere_api_key)
# compression_retriever = ContextualCompressionRetriever(
#     base_compressor=compressor, base_retriever=retriever
# )
#
# from langchain.retrievers.merger_retriever import MergerRetriever
# lotr = MergerRetriever(retrievers=[retriever, bm25_retriever])
#
# compressed_docs = compression_retriever.get_relevant_documents("为什么婆婆要把祥林嫂再嫁出去？")
# pretty_print_docs(compressed_docs)
query = "为什么婆婆要把祥林嫂再嫁出去？"
# docs = retriever.get_relevant_documents(query)
# pretty_print_docs(docs)

from langchain.retrievers.merger_retriever import MergerRetriever
lotr = MergerRetriever(retrievers=[retriever, bm25_retriever])

compressor = CohereRerank(cohere_api_key=cohere_api_key)
compression_retriever = ContextualCompressionRetriever(
    # base_compressor=compressor, base_retriever=retriever
    base_compressor=compressor, base_retriever=lotr
)
#
compressed_docs = compression_retriever.get_relevant_documents(query)
pretty_print_docs(compressed_docs)

messages = [
    SystemMessage(
        content="你是一个人工智能助手"),
]

llm = ChatOpenAI(model_name="gpt-3.5-turbo",
                 temperature=0,
                 openai_api_base="https://api.openai-proxy.org/v1",
                 openai_api_key="sk-06vk1oTAEV8hS51hapAQd9aVCyrBIEST1eizwHm4FcO2CpTe",
                 )

qa_template = "以下为背景知识：\n{context}\n请根据以上背景知识, 回答这个问题：{question}。"

prompt = PromptTemplate(
    template=qa_template,
    input_variables=["context", "question"]
)
chain_type_kwargs = {"prompt": prompt}

qa = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=compression_retriever,
    chain_type_kwargs=chain_type_kwargs,
)

app = Flask(__name__)

feedback_store = []

@app.route("/", methods=["GET", "POST"])
def home():
    response = ""
    if request.method == "POST":
        if 'query' in request.form:
            query = request.form["query"]
            response = qa.run(query=query)
            return render_template_string('''
                <!doctype html>
                <html lang="zh-cn">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>问答系统</title>
                    <style>
                        body {
                            font-family: Arial, sans-serif;
                            background-color: #f4f4f9;
                            margin: 0;
                            padding: 0;
                            display: flex;
                            justify-content: center;
                            align-items: center;
                            height: 100vh;
                        }
                        .container {
                            background: white;
                            padding: 20px;
                            border-radius: 8px;
                            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                            width: 90%;
                            max-width: 600px;
                            text-align: center;
                        }
                        input[type="text"] {
                            width: calc(100% - 22px);
                            padding: 10px;
                            margin-bottom: 10px;
                            border: 1px solid #ccc;
                            border-radius: 4px;
                        }
                        input[type="submit"] {
                            background-color: #007bff;
                            color: white;
                            border: none;
                            padding: 10px 20px;
                            border-radius: 4px;
                            cursor: pointer;
                            transition: background-color 0.3s;
                        }
                        input[type="submit"]:hover {
                            background-color: #0056b3;
                        }
                        h1 {
                            margin-bottom: 20px;
                        }
                        p {
                            background: #f9f9f9;
                            padding: 10px;
                            border-radius: 4px;
                            text-align: left;
                        }
                        .feedback-list {
                            margin-top: 20px;
                            text-align: left;
                        }
                    </style>
                </head>
                <body>
                    <div class="container">
                        <h1>输入你的问题</h1>
                        <form method="post">
                            <input type="text" name="query" placeholder="请输入问题">
                            <input type="submit" value="提交">
                        </form>
                        <h2>回复:</h2>
                        <p>{{response}}</p>
                        <h2>请对答案的满意度评分 (1-5):</h2>
                        <form method="post">
                            <input type="hidden" name="response" value="{{response}}">
                            <input type="number" name="rating" min="1" max="5">
                            <input type="submit" value="提交评分">
                        </form>
                        <div class="feedback-list">
                            <h2>历史满意度评价</h2>
                            <ul>
                            {% for feedback in feedback_store %}
                                <li>评分: {{ feedback['rating'] }} - 答案: {{ feedback['response'] }}</li>
                            {% endfor %}
                            </ul>
                        </div>
                    </div>
                </body>
                </html>
            ''', response=response, feedback_store=feedback_store)
        elif 'rating' in request.form:
            rating = request.form["rating"]
            response = request.form["response"]
            feedback_store.append({'response': response, 'rating': rating})
            return render_template_string('''
                <!doctype html>
                <html lang="zh-cn">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>问答系统</title>
                    <style>
                        body {
                            font-family: Arial, sans-serif;
                            background-color: #f4f4f9;
                            margin: 0;
                            padding: 0;
                            display: flex;
                            justify-content: center;
                            align-items: center;
                            height: 100vh;
                        }
                        .container {
                            background: white;
                            padding: 20px;
                            border-radius: 8px;
                            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                            width: 90%;
                            max-width: 600px;
                            text-align: center;
                        }
                        input[type="text"] {
                            width: calc(100% - 22px);
                            padding: 10px;
                            margin-bottom: 10px;
                            border: 1px solid #ccc;
                            border-radius: 4px;
                        }
                        input[type="submit"] {
                            background-color: #007bff;
                            color: white;
                            border: none;
                            padding: 10px 20px;
                            border-radius: 4px;
                            cursor: pointer;
                            transition: background-color 0.3s;
                        }
                        input[type="submit"]:hover {
                            background-color: #0056b3;
                        }
                        h1 {
                            margin-bottom: 20px;
                        }
                        p {
                            background: #f9f9f9;
                            padding: 10px;
                            border-radius: 4px;
                            text-align: left;
                        }
                        .feedback-list {
                            margin-top: 20px;
                            text-align: left;
                        }
                    </style>
                </head>
                <body>
                    <div class="container">
                        <h1>输入你的问题</h1>
                        <form method="post">
                            <input type="text" name="query" placeholder="请输入问题">
                            <input type="submit" value="提交">
                        </form>
                        <h2>感谢您的反馈！</h2>
                        <div class="feedback-list">
                            <h2>历史满意度评价</h2>
                            <ul>
                            {% for feedback in feedback_store %}
                                <li>评分: {{ feedback['rating'] }} - 答案: {{ feedback['response'] }}</li>
                            {% endfor %}
                            </ul>
                        </div>
                    </div>
                </body>
                </html>
            ''', feedback_store=feedback_store)
    return render_template_string('''
        <!doctype html>
        <html lang="zh-cn">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>问答系统</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    background-color: #f4f4f9;
                    margin: 0;
                    padding: 0;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    height: 100vh;
                }
                .container {
                    background: white;
                    padding: 20px;
                    border-radius: 8px;
                    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                    width: 90%;
                    max-width: 600px;
                    text-align: center;
                }
                input[type="text"] {
                    width: calc(100% - 22px);
                    padding: 10px;
                    margin-bottom: 10px;
                    border: 1px solid #ccc;
                    border-radius: 4px;
                }
                input[type="submit"] {
                    background-color: #007bff;
                    color: white;
                    border: none;
                    padding: 10px 20px;
                    border-radius: 4px;
                    cursor: pointer;
                    transition: background-color 0.3s;
                }
                input[type="submit"]:hover {
                    background-color: #0056b3;
                }
                h1 {
                    margin-bottom: 20px;
                }
                p {
                    background: #f9f9f9;
                    padding: 10px;
                    border-radius: 4px;
                    text-align: left;
                }
                .feedback-list {
                    margin-top: 20px;
                    text-align: left;
                }
            </style>
        </head>
        <body>
            <div class="container">
                <h1>输入你的问题</h1>
                <form method="post">
                    <input type="text" name="query" placeholder="请输入问题">
                    <input type="submit" value="提交">
                </form>
                <h2>回复:</h2>
                <p>{{response}}</p>
                <div class="feedback-list">
                    <h2>历史满意度评价</h2>
                    <ul>
                    {% for feedback in feedback_store %}
                        <li>评分: {{ feedback['rating'] }} - 答案: {{ feedback['response'] }}</li>
                    {% endfor %}
                    </ul>
                </div>
            </div>
        </body>
        </html>
    ''', feedback_store=feedback_store)

if __name__ == "__main__":
    app.run(debug=True)

#
# feedback_store = []
#
# @app.route("/", methods=["GET", "POST"])
# def home():
#     response = ""
#     if request.method == "POST":
#         if 'query' in request.form:
#             query = request.form["query"]
#             response = qa.run(query=query)
#             return render_template_string('''
#                 <!doctype html>
#                 <html lang="zh-cn">
#                 <head>
#                     <meta charset="UTF-8">
#                     <meta name="viewport" content="width=device-width, initial-scale=1.0">
#                     <title>问答系统</title>
#                     <style>
#                         body {
#                             font-family: Arial, sans-serif;
#                             background-color: #f4f4f9;
#                             margin: 0;
#                             padding: 0;
#                             display: flex;
#                             justify-content: center;
#                             align-items: center;
#                             height: 100vh;
#                         }
#                         .container {
#                             background: white;
#                             padding: 20px;
#                             border-radius: 8px;
#                             box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
#                             width: 90%;
#                             max-width: 600px;
#                             text-align: center;
#                         }
#                         input[type="text"] {
#                             width: calc(100% - 22px);
#                             padding: 10px;
#                             margin-bottom: 10px;
#                             border: 1px solid #ccc;
#                             border-radius: 4px;
#                         }
#                         input[type="submit"] {
#                             background-color: #007bff;
#                             color: white;
#                             border: none;
#                             padding: 10px 20px;
#                             border-radius: 4px;
#                             cursor: pointer;
#                             transition: background-color 0.3s;
#                         }
#                         input[type="submit"]:hover {
#                             background-color: #0056b3;
#                         }
#                         h1 {
#                             margin-bottom: 20px;
#                         }
#                         p {
#                             background: #f9f9f9;
#                             padding: 10px;
#                             border-radius: 4px;
#                             text-align: left;
#                         }
#                     </style>
#                 </head>
#                 <body>
#                     <div class="container">
#                         <h1>输入你的问题</h1>
#                         <form method="post">
#                             <input type="text" name="query" placeholder="请输入问题">
#                             <input type="submit" value="提交">
#                         </form>
#                         <h2>回复:</h2>
#                         <p>{{response}}</p>
#                         <h2>请对答案的满意度评分 (1-5):</h2>
#                         <form method="post">
#                             <input type="hidden" name="response" value="{{response}}">
#                             <input type="number" name="rating" min="1" max="5">
#                             <input type="submit" value="提交评分">
#                         </form>
#                     </div>
#                 </body>
#                 </html>
#             ''', response=response)
#         elif 'rating' in request.form:
#             rating = request.form["rating"]
#             response = request.form["response"]
#             feedback_store.append({'response': response, 'rating': rating})
#             return render_template_string('''
#                 <!doctype html>
#                 <html lang="zh-cn">
#                 <head>
#                     <meta charset="UTF-8">
#                     <meta name="viewport" content="width=device-width, initial-scale=1.0">
#                     <title>问答系统</title>
#                     <style>
#                         body {
#                             font-family: Arial, sans-serif;
#                             background-color: #f4f4f9;
#                             margin: 0;
#                             padding: 0;
#                             display: flex;
#                             justify-content: center;
#                             align-items: center;
#                             height: 100vh;
#                         }
#                         .container {
#                             background: white;
#                             padding: 20px;
#                             border-radius: 8px;
#                             box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
#                             width: 90%;
#                             max-width: 600px;
#                             text-align: center;
#                         }
#                         input[type="text"] {
#                             width: calc(100% - 22px);
#                             padding: 10px;
#                             margin-bottom: 10px;
#                             border: 1px solid #ccc;
#                             border-radius: 4px;
#                         }
#                         input[type="submit"] {
#                             background-color: #007bff;
#                             color: white;
#                             border: none;
#                             padding: 10px 20px;
#                             border-radius: 4px;
#                             cursor: pointer;
#                             transition: background-color 0.3s;
#                         }
#                         input[type="submit"]:hover {
#                             background-color: #0056b3;
#                         }
#                         h1 {
#                             margin-bottom: 20px;
#                         }
#                         p {
#                             background: #f9f9f9;
#                             padding: 10px;
#                             border-radius: 4px;
#                             text-align: left;
#                         }
#                     </style>
#                 </head>
#                 <body>
#                     <div class="container">
#                         <h1>输入你的问题</h1>
#                         <form method="post">
#                             <input type="text" name="query" placeholder="请输入问题">
#                             <input type="submit" value="提交">
#                         </form>
#                         <h2>感谢您的反馈！</h2>
#                     </div>
#                 </body>
#                 </html>
#             ''')
#     return render_template_string('''
#         <!doctype html>
#         <html lang="zh-cn">
#         <head>
#             <meta charset="UTF-8">
#             <meta name="viewport" content="width=device-width, initial-scale=1.0">
#             <title>问答系统</title>
#             <style>
#                 body {
#                     font-family: Arial, sans-serif;
#                     background-color: #f4f4f9;
#                     margin: 0;
#                     padding: 0;
#                     display: flex;
#                     justify-content: center;
#                     align-items: center;
#                     height: 100vh;
#                 }
#                 .container {
#                     background: white;
#                     padding: 20px;
#                     border-radius: 8px;
#                     box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
#                     width: 90%;
#                     max-width: 600px;
#                     text-align: center;
#                 }
#                 input[type="text"] {
#                     width: calc(100% - 22px);
#                     padding: 10px;
#                     margin-bottom: 10px;
#                     border: 1px solid #ccc;
#                     border-radius: 4px;
#                 }
#                 input[type="submit"] {
#                     background-color: #007bff;
#                     color: white;
#                     border: none;
#                     padding: 10px 20px;
#                     border-radius: 4px;
#                     cursor: pointer;
#                     transition: background-color 0.3s;
#                 }
#                 input[type="submit"]:hover {
#                     background-color: #0056b3;
#                 }
#                 h1 {
#                     margin-bottom: 20px;
#                 }
#                 p {
#                     background: #f9f9f9;
#                     padding: 10px;
#                     border-radius: 4px;
#                     text-align: left;
#                 }
#             </style>
#         </head>
#         <body>
#             <div class="container">
#                 <h1>输入你的问题</h1>
#                 <form method="post">
#                     <input type="text" name="query" placeholder="请输入问题">
#                     <input type="submit" value="提交">
#                 </form>
#                 <h2>回复:</h2>
#                 <p>{{response}}</p>
#             </div>
#         </body>
#         </html>
#     ''')
#
# if __name__ == "__main__":
#     app.run(debug=True)

# demo.launch(inbrowser=True)
# demo.launch(share=True)
# demo.launch(share=True, enable_queue=False, debug=True, show_api=False, server_port=8080, server_name="0.0.0.0")