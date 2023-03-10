// 2_chaining.js - Function chaining with D3
// CSCI3230U


// Create an SVG image
let canvas = d3.select("body")
    .append("svg")
    .attr("width", 500)
    .attr("height", 500);

// Append an ellipse
canvas.append('ellipse')
    .attr('cx', 110)
    .attr('cy', 60)
    .attr('rx', 100)
    .attr('ry', 50)
    .attr('style', "fill:yellow;stroke:purple;stroke-width:2")

// Add some text
canvas.append('text')
    .attr('x', 250)
    .attr('y', 50)
    .text('Filled ellipse');