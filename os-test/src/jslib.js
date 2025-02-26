// globals: start_time, displayState, updateDisplay

mergeInto(LibraryManager.library, {
    hal_millis: function() {
        return Date.now() - start_time
    },
    hal_matrix_set_arr: function(ptr) {
        let arr = new Uint8Array(Module.HEAP8.buffer, ptr, 8);
        //console.log(`Setting matrix to:`);
        //for (let i = 0; i < 8; i++) {
        //    console.log(arr[i].toString(2));
        //}
        // convert the array of ints to an array of arrays of booleans
        for (let i = 0; i < 8; i++) {
            let row = arr[i];
            let paddedByte = row.toString(2).padStart(8, '0');
            //console.log(`Padded byte for ${row}: ${paddedByte}`);
            let result = paddedByte.split('').map(function(bit) {
                return bit === '1';
            });
            //console.log(`Resulting row: ${result}`);
            displayState[i] = result;
        }
        //console.log(`Setting display to:`);
        //console.log(displayState);
        updateDisplay();
    },
    hal_matrix_get_arr: function(ptr) {
        let arr = new Int8Array(Module.HEAP8.buffer, ptr, 8);
        // convert an array of arrays of booleans to an array of ints
        for (let i = 0; i < 8; i++) {
            arr[i] = parseInt(displayState[i].map(function(bit) {
                return bit ? '1' : '0';
            }).join(''), 2);
        }
    },
    hal_button_get_state: function(button){
        console.log(`Button ${button} state requested`);
        // TODO: read the real button state
        return 0;
    },
    hal_tone: function(frequency) {
        console.log(`Playing tone at ${frequency} Hz`);
        // TODO: play the tone
    },
    hal_tone_off: function() {
        console.log(`Stopping tone`);
    },
    hal_console_write: function(ptr) {
        console.log(UTF8ToString(ptr));
    }
});