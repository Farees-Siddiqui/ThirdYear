// 4_scatter.js - Simple scatter plot with D3
// CSCI3230U

window.onload = function () {
    // Set overall Dimensions
    // SVG sizes
    const xSize = 500;
    const ySize = 500;
    const margin = 40;
    const xMax = xSize - margin * 2;
    const yMax = ySize - margin * 2;

    // Create Random Points
    const numPoints = 100;
    const data = [];
    for (let i = 0; i < numPoints; i++) {
        data.push([Math.random() * xMax, Math.random() * yMax]);
    }

    // Append SVG Object to the Page
    // Here we use a grouped svg object
    // See - https://jenkov.com/tutorials/svg/g-element.html
    const svg = d3.select("#myPlot")
        .append("svg")
        .append("g")
        .attr("transform", "translate(" + margin + "," + margin + ")");

    // X Axis
    const x = d3.scaleLinear()
        .domain([0, 500])
        .range([0, xMax]);

    svg.append("g")
        .attr("transform", "translate(0," + yMax + ")")
        .call(d3.axisBottom(x));

    // Y Axis
    const y = d3.scaleLinear()
        .domain([0, 500])
        .range([yMax, 0]);

    svg.append("g")
        .call(d3.axisLeft(y));

    // Dots
    svg.append('g')
        .selectAll("dot")
        .data(data).enter()
        .append("circle")
        .attr("cx", function (d) { return d[0] })
        .attr("cy", function (d) { return d[1] })
        .attr("r", 3)
        .style("fill", "Red");
}