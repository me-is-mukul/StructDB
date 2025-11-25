
## compiling gemini file
```bash
g++ src/gemini.cpp -o gemini -lcurl -std=c++17
```
## compiling everything
```bash
g++ src/Graph.cpp src/main.cpp src/MaxHeap.cpp src/ProgressTracker.cpp -I include -o app   
```
