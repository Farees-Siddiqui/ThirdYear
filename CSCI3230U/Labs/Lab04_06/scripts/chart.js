function getGrade(mark) {
    if (mark < 50.0) {
        return 'F';
    } else if (mark < 60.0) {
        return 'D';
    } else if (mark < 70.0) {
        return 'C';
    } else if (mark < 80.0) {
        return 'B';
    } else {
        return 'A';
    }
}

let colVals = [];
let rowVals = [];
let charVals = [];

const margin = { top: 20, right: 20, bottom: 30, left: 15 };
const width = 400 - margin.left - margin.right;
const height = 400 - margin.top - margin.bottom;

const svg = d3.select("#chart")
    .attr("width", 600)
    .attr("height", 600)
    .append("g")
    .attr("transform", "translate(50, 30)");

function getFrequencies(marks) {
    let freq = {
        'A': 0,
        'B': 0,
        'C': 0,
        'D': 0,
        'F': 0
    };
    let total = marks.length;
    marks.forEach(function (mark) {
        freq[getGrade(mark)]++;
    });
    for (let key in freq) {
        freq[key] = freq[key] / total;
    }
    return freq;
}

function generateBarChart() {
    // Convert the charVals dictionary into an array of objects
    svg.selectAll("*").remove();
    const data = Object.keys(charVals).map(key => ({ label: key, value: charVals[key] }));

    const xScale = d3.scaleBand()
        .domain(data.map(d => d.label))
        .range([0, width])
        .padding(0.1);

    const yScale = d3.scaleLinear()
        .domain([0, d3.max(data, d => d.value)])
        .range([height, 0]);

    const colorScale = d3.scaleLinear()
        .domain([0, d3.max(data, d => d.value)])
        .range(['white', 'blue']);

    // Update the bars with new data
    const bars = svg.selectAll("rect")
        .data(data);

    bars.exit().remove();

    bars.enter().append("rect")
        // make the intensity of the color depend on the value without using interpolateBlues
        .attr("fill", d => colorScale(d.value))
        .merge(bars)
        .transition()
        .duration(500)
        .attr("x", d => xScale(d.label))
        .attr("y", d => yScale(d.value))
        .attr("width", xScale.bandwidth())
        .attr("height", d => height - yScale(d.value));

    // Add the x-axis
    svg.append("g")
        .attr("class", "x-axis")
        .attr("transform", `translate(0, ${height})`)
        .call(d3.axisBottom(xScale));

    // Add the x-axis label
    svg.append("text")
        .attr("class", "axis-label")
        .attr("x", width / 2)
        .attr("y", height + margin.bottom / 2)
        .attr("text-anchor", "middle")
        .attr("transform", "translate(0, 20)")
        .text("X Axis Label");

    // Add the y-axis
    svg.append("g")
        .attr("class", "y-axis")
        .call(d3.axisLeft(yScale));

    // Add the y-axis label
    svg.append("text")
        .attr("class", "axis-label")
        .attr("transform", "translate(-20, 0) rotate(-90)")
        .attr("x", -height / 2)
        .attr("y", -margin.left)
        .attr("text-anchor", "middle")
        .text("Y Axis Label");
}

