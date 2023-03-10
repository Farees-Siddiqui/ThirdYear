// 3_events.js - Events in jQuery
// CSCI3230U

$(document).ready(function () {
    $('p').click(function () {
        console.log('A paragraph (somewhere) has been clicked');
    });

    $("#target").focus(function () {
        console.log("Handler for .focus() called.");
    });

    $("#field2").mouseenter(function () {
        console.log("Handler for .mouseenter() called.");
    });
    
});