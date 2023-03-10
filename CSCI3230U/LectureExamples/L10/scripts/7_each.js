// 7_each.js - For each
// CSCI3230U

$(document).ready(() => {

    // Add an event
    $(document.body).click(function () {
        // Iterate over all items
        $("div").each(function (i) {
            // For even elements only, change the color to green
            if (i % 2 === 0 & this.style.color !== "green") {
                this.style.color = "green";
            } else {
                this.style.color = "";
            }
        });
    });

});