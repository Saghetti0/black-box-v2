# how to build the wasm (needed whenever C or jslib.js changes)
1. install emscripten
2. windows: run `emcc .\os-test\src\plat_main_wasm.c .\os-test\src\plat_hal_wasm.c -o .\os-test\site\plat_main.js -I .\os-test\include\ --js-library .\os-test\src\jslib.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_test_stuff']"`, macos/linux: run `emcc ./os-test/src/plat_main_wasm.c ./os-test/src/plat_hal_wasm.c -o ./os-test/site/plat_main.js -I ./os-test/include/ --js-library ./os-test/src/jslib.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_test_stuff']"`

...for now, anyways. building in the browser comes later (maybe with [emception](https://github.com/jprendes/emception)? or we could just have a server that builds the c in a normal x86 env.)

so basically plat_main_wasm is right now just an entry point and isn't doing its real job. it's just letting me call test functions in C to see if everything works. plat_hal_wasm is in its near-finished form, which really just means that it's forwarding all the calls to the JavaScript library in `jslib.js`. That's where the code that interacts with the UI will go, once I have a full UI implemented. 