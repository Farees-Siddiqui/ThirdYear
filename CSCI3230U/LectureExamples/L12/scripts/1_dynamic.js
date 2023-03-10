// 1_dynamic.js - Dynamic properties with D3
// CSCI3230U

// Change paragraph colours dynamically
let colours = ['blue', 'red', 'green', 'cornflowerblue', 'orange'];

d3.selectAll("p")
    .style("color", (data, index) => {
        return colours[index];
    });

// Alternate colour of list items
d3.selectAll("li")
    .style("color", function (d, i) {
        return i % 2 ? "gray" : "purple";
    });

// Unpacking the meaning of data
let data = ['D1', 'D2', 'D3'];
let paragraph = d3.select("body")
    .selectAll("p")
    .data(data)
    .text(function (d, i) {
        console.log("d: " + d);
        console.log("i: " + i);
        console.log("this: " + this);

        return d;
    });