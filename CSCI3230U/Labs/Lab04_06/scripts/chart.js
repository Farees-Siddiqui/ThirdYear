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

$("th.col_th").each(function(index) {
    $(this).click(function() {
        colVals = [];
        charVals = [];
        var column = $("tr td:nth-child(" + (index + 2) + ")");
        console.log("clicked column " + index);
        
        column.each(function() {
            colVals.push(parseFloat($(this).text()));
        });
        charVals = getFrequencies(colVals);
        console.log(charVals);
    });
});

// each time a row is selected, append each value in the row to an array
$("th.row_th").each(function(index) {
    $(this).click(function() {
        rowVals = [];
        charVals = [];
        var row = $("tr").eq(index + 1);
        console.log("clicked row " + index);
        
        row.find("td").each(function() {
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
    marks.forEach(function(mark) {
        freq[getGrade(mark)]++;
    });
    for (let key in freq) {
        freq[key] = freq[key] / total;
    }
    return freq;
}
