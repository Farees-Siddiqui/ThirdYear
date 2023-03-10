// 4_adding.js - Adding elements to DOM
// CSCI3230U

// Adding an element to our DOM
d3.select("body")
    .append("p")
    .attr("id", "dynamicParagraph")
    .text("This is a brand new paragraph")
    .style("color", "red");
