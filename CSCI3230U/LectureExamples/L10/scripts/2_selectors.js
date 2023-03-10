// 2_selector.js - Use css selectors
// CSCI3230U

$(document).ready(() => {
    console.log('ready');

    // CSS selectors
    // Grab table data
    let td = $('td');
    console.log('td: ', td.length);

    // Select p children
    console.log('div > p: ', $('div > p').length);

    // Select p descendents
    console.log('div p: ', $('div p').length)

    // Even elements
    console.log('td:even: ', $('td:even').length);

    // Explore these in your browser's JavaScript console
    //
    // Pattern matching
    // Select only td 
    $('td[title="fred"]')[0]
    // Starting with fred
    $('td[title^="fred"]')
    // ending with fred
    $('td[title$="fred"]')
    $('td[title*="fred"]')
    $(':contains("fred")')
});