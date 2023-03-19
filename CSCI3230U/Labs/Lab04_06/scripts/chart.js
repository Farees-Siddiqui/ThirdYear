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

const margin = { top: 20, right: 20, bottom: 30, left: 50 };
const width = 400 - margin.left - margin.right;
const height = 400 - margin.top - margin.bottom;

const svg = d3.select("#chart")
    .attr("width", 400)
    .attr("height", 400)
    .append("g")
    .attr("transform", "translate(50, 30)");

    

$("th.col_th").each(function (index) {
    $(this).click(function () {
        colVals = [];
        charVals = [];
        var column = $("tr td:nth-child(" + (index + 2) + ")");
        console.log("clicked column " + index);

        column.each(function () {
            colVals.push(parseFloat($(this).text()));
        });
        charVals = getFrequencies(colVals);
        console.log(charVals);
        generateBarChart();
    });
});

// each time a row is selected, append each value in the row to an array
$("th.row_th").each(function (index) {
    $(this).click(function () {
        rowVals = [];
        charVals = [];
        var row = $("tr").eq(index + 1);
        console.log("clicked row " + index);

        row.find("td").each(function () {
            rowVals.push(parseFloat($(this).text()));
        });
        charVals = getFrequencies(rowVals);
        console.log(charVals);
    });
});

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
        .range([height, 0]);

    // Update the bars with new data
    const bars = svg.selectAll("rect")
        .data(data);

    bars.exit().remove(); 

    bars.enter().append("rect") 
        // make the intensity of the color depend on the value without using interpolateBlues
        .attr("fill", "steelblue")
        .merge(bars) 
        .transition()
        .duration(500)
        .attr("x", d => xScale(d.label))
        .attr("y", d => yScale(d.value))
        .attr("width", xScale.bandwidth())
        .attr("height", d => height - yScale(d.value));

    // Update the x-axis with new labels
    const xAxis = d3.axisBottom(xScale);
    svg.select(".x-axis")
        .transition()
        .duration(500)
        .call(xAxis);

    svg.append("g")
        .attr("class", "x-axis")
        .attr("transform", `translate(0, ${height})`)
        .call(xAxis)
        .append("text")
        .attr("class", "axis-label")
        .attr("x", width / 2)
        .attr("y", margin.bottom / 2)
        .attr("text-anchor", "middle")
        .text("X Axis Label");

    // Label the y-axis
    svg.append("g")
        .attr("class", "y-axis")
        .call(d3.axisLeft(yScale))
        .append("text")
        .attr("class", "axis-label")
        .attr("transform", "rotate(-90)")
        .attr("x", -height / 2)
        .attr("y", -margin.left)
        .attr("text-anchor", "middle")
        .text("Y Axis Label");
}
