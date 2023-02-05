// add your code here

function buildGameBoard(board) {
    // get the table element to append the cells
    let table = document.getElementById("board");

    // loop through the board array
    for (let i = 0; i < board.length; i++) {
        // create a new row
        let row = document.createElement("tr");
        row.setAttribute("class", "mainBoard")

        for (let j = 0; j < board[i].length; j++) {
            // create a new cell
            let cell = document.createElement("td");
            cell.innerHTML = board[i][j] > 0 ? board[i][j] : "";
            cell.classList.add("cell");

            // give the cell a name
            cell.setAttribute("name", `cell${i + 1}${j + 1}`);
            cell.setAttribute("class", "mainBoard");
            cell.classList.add("cell");
            // add the cell to the row
            row.appendChild(cell);
        }

        // add the row to the table
        table.appendChild(row);
    }
    console.log(table);
}
function sameBlock(x1, y1, x2, y2) {
    let firstRow = Math.floor(y1 / 3) * 3;
    let firstCol = Math.floor(x1 / 3) * 3;
    return (y2 >= firstRow && y2 <= (firstRow + 2) && x2 >= firstCol && x2 <= (firstCol + 2));
}

function sameRow(x1, y1, x2, y2) {
    return y1 == y2;
}

function sameColumn(x1, y1, x2, y2) {
    return x1 == x2;
}

let board = [
    [5, 3, -1, -1, 7, -1, -1, -1, -1],
    [6, -1, -1, 1, 9, 5, -1, -1, -1],
    [-1, 9, 8, -1, -1, -1, -1, 6, -1],
    [8, -1, -1, -1, 6, -1, -1, -1, 3],
    [4, -1, -1, 8, -1, 3, -1, -1, 1],
    [7, -1, -1, -1, 2, -1, -1, -1, 6],
    [-1, 6, -1, -1, -1, -1, 2, 8, -1],
    [-1, -1, -1, 4, 1, 9, -1, -1, 5],
    [-1, -1, -1, -1, 8, -1, -1, 7, 9]
]
buildGameBoard(board);
let moves = [];

// keep track of the active digit
let activeDigit;

// get all cells in the game board
const cells = document.querySelectorAll('.cell');

// add click event listener to each cell in the game board
cells.forEach((cell) => {
    cell.addEventListener('click', (event) => {
        // if an active digit is set, place the digit in the cell
        if (activeDigit) {
            event.target.textContent = activeDigit;
            moves.push(event.target.textContent);
            highlightConflicts(event.target);

            activeDigit = undefined;
            const numbers = document.querySelectorAll('.numbers');
            numbers.forEach((number) => {
                number.classList.remove('user-input');
            });
        }
    });
});

const numbers = document.querySelectorAll('.numbers');

numbers.forEach((number) => {
    number.addEventListener('click', (event) => {
        // set the active digit
        activeDigit = event.target.textContent;
        event.target.classList.add('user-input');
    });
});

function highlightConflicts(cell) {
    const x = cell.cellIndex;
    const y = cell.parentElement.rowIndex;

    cells.forEach((otherCell) => {
        const otherX = otherCell.cellIndex;
        const otherY = otherCell.parentElement.rowIndex;

        if ((otherX === x || otherY === y || sameBlock(x, y, otherX, otherY)) && otherCell !== cell) {
            otherCell.classList.add('error');
        }
    });
}