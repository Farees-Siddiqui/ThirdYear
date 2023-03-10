// implement `selectRow(rowIndex)` using JQuery - selects every non-header cell in the specified row (indexed, starting with zero)
/* the following is the definition of the table:

<table class="center spreadsheet" id="spreadsheet">
    <tr>
      <th>Student ID</th>
      <th class="col_th">Asmt 1</th>
      <th class="col_th">Asmt 2</th>
      <th class="col_th">Asmt 3</th>
    </tr>

    <tr>
      <th class="row_th">100000000</th>
      <td>4.5</td>
      <td>3.75</td>
      <td>3.4</td>
    </tr>

    <tr>
      <th class="row_th">100000001</th>
      <td>4.25</td>
      <td>4.12</td>
      <td>4.25</td>
    </tr>

    <tr>
      <th class="row_th">100000002</th>
      <td>5.0</td>
      <td>4.75</td>
      <td>4.5</td>
    </tr>

  </table>
  
  select row should only select the td elements, not the th elements

  */

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

// use jquery to get all the th elements that have the class col_th
// and add a click event handler to each of them
// the event handler should call the selectColumn function with the index of the column
// as the argument
$("th.col_th").each(function(index) {
    $(this).click(function() {
        selectColumn(index+1);
        console.log("clicked column " + index);
    });
});

$("th.row_th").each(function(index) {
    $(this).click(function() {
        selectRow(index);
        console.log("clicked row " + index);
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