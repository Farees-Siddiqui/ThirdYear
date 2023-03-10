// 2_object_creation.js - Object constructor and object literal
// CSCI3230U

// Object constructor
function Course(code, name) {
    this.courseCode = code;
    this.courseName = name;
    this.classList = [{ "sid": "100000001", "fName": "Phillip", "lName": "Fry" },
    { "sid": "100000002", "fName": "Turanga", "lName": "Leela" },
    { "sid": "100000003", "fName": "Amy", "lName": "Wong" },
    { "sid": "100000004", "fName": "Bender", "lName": "Rodrig'z" },
    { "sid": "100000005", "fName": "Hermes", "lName": "Conrad" }
    ];
    this.toString = function () {
        return this.courseCode + " " +
            this.courseName +
            ", students " +
            this.classList;
    }
}
// Creat new instance
let csci3230u = new Course('CSCI3230u', 'Web Application Development');

// Object literal example
let courseInstance = {
    courseCode: "CSCI3230u",
    courseName: "Web Application Development",
    classList: [
        { "sid": "100000001", "fName": "Phillip", "lName": "Fry" },
        { "sid": "100000002", "fName": "Turanga", "lName": "Leela" },
        { "sid": "100000003", "fName": "Amy", "lName": "Wong" },
        { "sid": "100000004", "fName": "Bender", "lName": "Rodrig'z" },
        { "sid": "100000005", "fName": "Hermes", "lName": "Conrad" }
    ],
    location: null
}  
