let averageRatings = {};
$(document).ready(function () {
   // add your code here
   loadReviews().then(data => {
      // construct the table here
      let table = $('<table class="table is-hoverable">');
      let headerRow = $('<tr>');
      headerRow.append(createTableHeader('ID'));
      headerRow.append(createTableHeader('Title'));
      headerRow.append(createTableHeader('Author'));
      headerRow.append(createTableHeader('Price'));
      headerRow.append(createTableHeader('Rating'));
      table.append(headerRow);
      for (let i = 0; i < data.length; i++) {
         let row = $('<tr>');
         row.append(createTableCell(data[i].id));
         row.append(createTableCell(data[i].title));
         row.append(createTableCell(data[i].author));
         row.append(createTableCell(data[i].price));
         row.append(createTableCell(data[i].rating));
         table.append(row);
      }
      $('#rating_table').append(table);
      let sum = 0;
      let count = 0;
      for (let i = 0; i < data.length; i++) {
         sum += data[i].rating;
         count++;
         averageRatings[data[i].id] = sum / count;
      }
      let chartData = Object.keys(averageRatings).map(key => ({id: key, rating: averageRatings[key]}));
      let margin = {top: 20, right: 20, bottom: 70, left: 40},
         width = 600 - margin.left - margin.right,
         height = 300 - margin.top - margin.bottom;
      let x = d3.scaleLinear().range([0, width]);
      let y = d3.scaleBand().range([height, 0]).padding(0.1);
      let svg = d3.select("#rating_chart")
         .append("svg")
         .attr("width", width + margin.left + margin.right)
         .attr("height", height + margin.top + margin.bottom)
         .append("g")
         .attr("transform",
            "translate(" + margin.left + "," + margin.top + ")");
      x.domain([0, d3.max(chartData, function (d) {
         return d.rating;
      })]);
      y.domain(chartData.map(function (d) {
         return d.id;
      }));
      svg.selectAll("rect")
         .data(chartData)
         .enter().append("rect")
         .attr("y", function (d) {
            return y(d.id);
         })
         .attr("height", y.bandwidth())
         .attr("x", 0)
         .attr("width", function (d) {
            return x(d.rating);
         })
         .attr("fill", "hsl(348, 100%, 61%)");
      svg.append("g")
         .attr("transform", "translate(0," + height + ")")
         .call(d3.axisBottom(x));
      svg.append("g")
         .call(d3.axisLeft(y));
   });

});

// here are some helper functions
// you are *not* required to use them

function createTableCell(content) {
   const cell = $('<td>');
   cell.text(content);
   return cell;
}

function createTableHeader(content) {
   const header = $('<th>');
   header.text(content);
   return header;
}

function loadReviews() {
   return fetch("data.json")
      .then(response => response.json())
      .then(data => {
         return data;
      })
      .catch(error => console.error(error));
}
