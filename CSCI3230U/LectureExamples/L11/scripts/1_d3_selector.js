// 1_d3_selector.js - Basic selection with D3
// CSCI3230U

// Select all paragraphs, make them yellow
d3.selectAll("p").style("color", "yellow");

// Select body and colour
d3.select("body").style("background-color", "grey");

// Select CSS odd class, colour purple
d3.selectAll(".odd").style("color", "purple")

// Append to the DOM
d3.select("body").append("h2").text("H2 added dynamically by D3!").style("color", "darkred");
