// 3_json_basics.js - Working with JSON
// CSCI3230U

// Declare JSON string
const json = '{"firstName":"Robert","lastName":"Smith","age":"29","birthPlace":"Prince George"}';
// Parse JSON (JSON_to_JS)
const obj = JSON.parse(json);

// Array as string
const json_array = '[{ "sid": "100000001", "fName": "Phillip", "lName": "Fry" },\
{ "sid": "100000002", "fName": "Turanga", "lName": "Leela" },\
{ "sid": "100000003", "fName": "Amy", "lName": "Wong" },\
{ "sid": "100000004", "fName": "Bender", "lName": "Rodrig\'z" },\
{ "sid": "100000005", "fName": "Hermes", "lName": "Conrad" }]'
// Parse JSON
const obj2 = JSON.parse(json_array);

// Stringify object (JS_to_JSON)
const customer = {
    firstName: 'Robert',
    lastName: 'Smith',
    age: 29,
    birthPlace: 'Prince George'
};
// Convert JS object to JSON string
const customerJSON = JSON.stringify(customer);