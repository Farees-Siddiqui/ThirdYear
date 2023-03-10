// 3_binding.js - Data binding in D3
// CSCI3230U

let dataArray = [1, 2, 3, 4, 5];
let colours = ['blue', 'red', 'green', 'cornflowerblue', 'orange'];

let circles = d3.select("body")
    .selectAll("circle")
    .data(dataArray)
    .attr("fill", "blue");


let myData = ["Hello World!", "Lets replace me", "with more text"];
let p = d3.select("body")
    .selectAll("p")
    .data(myData)
    .text(function (d) {
        return d;
    });