// 5_effects.js - Effects with jQuery
// CSCI3230U

$(document).ready(() => {
    $("#animatebutton").click(function () {
        $("p").animate(
            { fontSize: "24pt" },
            3000, "swing")
    });

    $("#runqueuebutton").click(function () {
        $("#myDiv")
            .show("slow")
            .animate({ left: "+=200" }, 2000)
            .slideToggle(1000)
            .slideToggle("fast")
            .animate({ left: "-=200" }, 1500)
            .hide("slow")
            .show(1200)
            .slideUp("normal");
    });
});
