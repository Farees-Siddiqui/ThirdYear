// 8_getset.js - Each of getting and setting DOM content
// CSCI3230U

$(document).ready(() => {
    // Getter methods
    //
    // Show text of the <p>
    $("#get_text").click(function () {
        alert("Text: " + $("#my_paragraph").text());
    });
    // Show HTML of the <p>
    $("#get_html").click(function () {
        alert("HTML: " + $("#my_div").html());
    });
    // Show the value
    $("#submit").click(function () {
        alert("Value: " + $("#input1").val());
    });

    // Setter methods
    //
    // Show text of the <p>
    $("#set_text").click(function () {
        $('#my_paragraph').text("My text has changed");
    });

    // Show HTML of the <p>
    $("#set_html").click(function () {
        $('#my_paragraph').html("<h2>I am now a header!</h2>");
    });

    // Set value of field
    $("#set_value").click(function(){
        $("#username2").val("TypeScript");
      });
});