// 9_css.js - Manipulating CSS
// CSCI3230U

$(document).ready(function(){
    // Toggle beteen add and remove a CSS class
    $("#toggle_css").click(function(){
      $("li, h1").toggleClass("plum");
    });

    // Remove a CSS class
    $("#remove_css").click(function(){
        $("li").removeClass("plum");
      });

      $("#add_css").click(function(){
        $("h2").addClass("olive");
      });

      $("#general_css").click(function(){
        $(document.body).css("background-color", "yellow");
      });
  });