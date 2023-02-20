// add your code here
// Define an array of JavaScript objects
const data = [
    {col1: "2021/01/17", col2: "3:41"},
    {col1: "2021/01/21", col2: "4:01"},
    {col1: "2021/02/01", col2: "2:52"},
    {col1: "2021/02/17", col2: "3:08"},
    {col1: "2021/03/01", col2: "2:51"}
];

// Get the table body element
const tableBody = document.getElementById("table-body");

// Loop through the data array and create a new row for each object
data.forEach(item => {
    // Create a new row element
    const row = document.createElement("tr");

    // Create two new cell elements, one for each column
    const col1 = document.createElement("td");
    const col2 = document.createElement("td");

    const h1 = document.createElement("th");
    const h2 = document.createElement("th");

    row.setAttribute("class", "scores");
    col1.setAttribute("class", "scores");
    col2.setAttribute("class", "scores");
    h1.setAttribute("class", "scores");
    h2.setAttribute("class", "scores");

    // Set the text content of each cell to the values in the object
    col1.textContent = item.col1;
    col2.textContent = item.col2;

    // Append the cells to the row
    row.appendChild(col1);
    row.appendChild(col2);

    // Append the row to the table body
    tableBody.appendChild(row);
});