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

$("th.col_th").each(function(index) {
    $(this).click(function() {
        selectColumn(index+1);
        // console.log("clicked column " + index);
    });
});

$("th.row_th").each(function(index) {
    $(this).click(function() {
        selectRow(index);
        // console.log("clicked row " + index);
    });
});

$("table.spreadsheet td").click(function() {
    var cell = $(this);
    var text = cell.text();
    var input = $("<input type='text' value='" + text + "'/>");
    cell.html(input);
    input.focus();
    input.select();
    deselectAll();
    cell.addClass("selected");
    input.keypress(function(event) {
        if (event.which == 13) {
            cell.text(input.val());
        }
        cell.removeClass("selected")
    });
    
    input.blur(function() {
        cell.text(input.val());
        cell.removeClass("selected")
    });
});