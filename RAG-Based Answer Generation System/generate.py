#!/usr/bin/env python
# -*- coding:utf-8 _*-
"""
@author:quincy qiang
@license: Apache Licence
@file: generate.py
@time: 2023/04/17
@contact: yanqiangmiffy@gamil.com
@software: PyCharm
@description: coding..
"""

import os
import requests
from typing import Dict, Union, Optional, Mapping, Any, List

from langchain_core.callbacks import CallbackManagerForLLMRun
from langchain.llms.base import LLM
from langchain.llms.utils import enforce_stop_tokens


class llama_chinese(LLM):
    # api_url: Optional[str] = "http://219.216.64.75:31816/v1/completions"
    api_url: Optional[str] = "http://219.216.64.127:27031/v1/completions"
    max_token: int = 5000
    temperature: float = 0.1
    top_p: float = 0.9
    history:  List[List] = []
    with_history: bool = False
    model_kwargs: Optional[dict] = None

    @property
    def _llm_type(self) -> str:
        return "llama_chinese"

    @property
    def _identifying_params(self) -> Mapping[str, Any]:
        """Get the identifying parameters."""
        _model_kwargs = self.model_kwargs or {}
        return {
            **{"api_url": self.api_url},
            **{"model_kwargs": _model_kwargs},
        }

    def _call(
            self,
            prompt: str,
            stop: Optional[List[str]] = None,
            run_manager: Optional[CallbackManagerForLLMRun] = None,
            **kwargs: Any,
    ) -> str:

        _model_kwargs = self.model_kwargs or {}

        headers = {'Content-Type': 'application/json'}

        # messages = [
        #     {
        #         "role": "system",
        #         "content": "You are ChatGLM3, a large language model trained by Zhipu.AI. Follow the user's "
        #         "instructions carefully. Respond using markdown.",
        #     },
        #     {
        #         "role": "user",
        #         "content": prompt,
        #     }
        # ]

        payload = {
            "input": prompt,
            "temperature": 0.8,
            # "history": self.history,
            "max_tokens": 2000,
            "top_p": 0.9,
        }
        payload.update(kwargs)
        payload.update(_model_kwargs)

        try:
            response = requests.post(
                self.api_url, json=payload, headers=headers, timeout=300)
        except requests.exceptions.RequestException as e:
            raise ValueError(f'Error raised by inference endpoint: {e}')

        if response.status_code != 200:
            raise ValueError(f'Failed with response: {response}')

        parsed_response = response.json()
        text = parsed_response['choices'][-1]['text']

        if stop is not None:
            text = enforce_stop_tokens(text, stop)

        if self.with_history:
            self.history = self.history + [[prompt, text]]
        return text


# if __name__ == '__main__':
#     llm = llama_chinese()
#     print(llm("东北大学怎么样？"))
