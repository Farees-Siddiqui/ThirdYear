function deselectAll() {
    $("table.spreadsheet tr td").removeClass("selected");
    $("table.spreadsheet tr").removeClass("selected");
}

function selectRow(rowIndex) {
    deselectAll();
    var row = $("tr").eq(rowIndex + 1);
    row.addClass("selected")
}

function selectColumn(columnIndex) {
    deselectAll();
    var column = $("tr td:nth-child(" + (columnIndex + 1) + ")");
    column.addClass("selected");
}

fetch('http://localhost:5500/grades.csv')
    .then(response => response.text())
    .then(text => {
        const data = d3.csvParse(text);

        console.log(data);
        // construct the table
        const table = d3.select('#spreadsheet');

        // append the header row
        table.append('tr')
            .selectAll('th')
            .data(data.columns)
            .enter()
            .append('th')
            .text(function (column) {
                return column;
            })
            .attr("class", "col_th");

        // create a row for each object in the data
        const rows = table.selectAll('tr')
            .data(data)
            .enter()
            .append('tr');

        // create a cell in each row for each column
        const cells = rows.selectAll('td')
            .data(function (row) {
                return data.columns.map(function (column) {
                    return { column: column, value: row[column] };
                });
            })
            .enter()
            .append('td')
            .text(function (d) {
                return d.value;
            });

        $("table.spreadsheet tr td:first-child").each(function () {
            $(this).replaceWith(function () {
                return $("<th/>", {
                    html: $(this).html()
                });
            });
        });
        $("table.spreadsheet tr th:first-child").addClass("row_th");

        $("table.spreadsheet tr th:first-child").removeClass("col_th");

        $("th.col_th").each(function (index) {
            $(this).click(function () {
                selectColumn(index + 1);
                console.log("clicked column " + index);
            });
        });

        $("th.row_th").each(function (index) {
            $(this).click(function () {
                selectRow(index - 1);
                // console.log("clicked row " + index);
            });
        });

        $("table.spreadsheet td").click(function () {
            var cell = $(this);
            var text = cell.text();
            var input = $("<input type='text' value='" + text + "'/>");
            cell.html(input);
            input.focus();
            input.select();
            deselectAll();
            cell.addClass("selected");
            input.keypress(function (event) {
                if (event.which == 13) {
                    cell.text(input.val());
                    generateBarChart();
                }
                cell.removeClass("selected")
            });

            input.blur(function () {
                cell.text(input.val());
                generateBarChart();
                cell.removeClass("selected")
            });
        });

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
        console.log(table.node());
    });
