// 6_traversal.js - Traversing the DOM
// CSCI3230U

$(document).ready(() => {
    // Get our div container
    let my_div = $('#myDiv').children();
    console.log('Do we have a jQuery object: ', my_div instanceof jQuery);

    // Get all descendant list items
    let my_li = my_div.find('li');
    console.log('Do we have a jQuery object: ', my_li instanceof jQuery);

    // Get the second list item
    let item_2 = my_li.eq(1);

    // Get my siblings (but not myself)
    let all_li = item_2.siblings();

    // Get myself back
    let item_2b = item_2
        .siblings()
        .first()
        .next();

    // Do we have the same object?
    console.log('Same list item: ', item_2[0] === item_2b[0]);

    // Get our odd and not-odd list items
    let odd_items = $('li').filter('.odd');
    let not_odd = $('li').not('.odd');

    
});