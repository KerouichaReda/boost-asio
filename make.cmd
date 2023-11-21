@echo off
cmake -Hprojects\synchronous\src -Bbuild/synchronous
cmake -Hprojects\asynchronous\src -Bbuild/asynchronous
