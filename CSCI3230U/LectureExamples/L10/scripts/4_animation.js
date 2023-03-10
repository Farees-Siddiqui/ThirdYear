// 4_animation.js - Animation with jQuery
// CSCI3230U

let right_properties = {
    left: '250px',
    opacity: '0.5',
    height: '150px',
    width: '150px'
}

let left_properties = {
    left: '0px',
    opacity: '0.5',
    height: '100px',
    width: '100px'
}

function animRight() {
    $("div").animate(right_properties, "slow", "swing", animLeft);
}

function animLeft() {
    $("div").animate(left_properties, "fast", "swing");
}

$(document).ready(() => {
    $("button").click(animRight);
});

