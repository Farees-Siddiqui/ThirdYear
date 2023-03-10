// 1_objects.js - What do we have here?
// CSCI3230U


function square(x) {
    square.counter++;
    return x * x;
}

square.help = "square(x) is x*x.";
square.counter = 0;
square[1] = 1;
square[2] = 4;

for (let i = 0; i < square(square[2]); i += 1) {
    console.log(i + ": " + square.help);
}
// What is output?
console.log("Num calls: " + square.counter);

// Number of parameters square takes
square.length
// Name of function
square.name
// Property tracked function calls
square.counter = 0;