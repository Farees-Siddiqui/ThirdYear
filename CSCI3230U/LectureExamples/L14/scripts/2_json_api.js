window.onload = function () {
    let button = document.getElementById('loadDataButton');
    button.onclick = function () {
        fetch('https://jsonplaceholder.typicode.com/todos')
            .then((response) => response.json())
            .then((json) => {
                x = json;
                // Get list of keys in object
                keys = Object.keys(x);
                // keys.length
                // keys[0]
                // keys['0']
                // keys.1 does not work, as it is not a valid identifier, see:
                // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Property_accessors
                let content = document.getElementById('content');
                let ol = document.createElement('ol');
                content.appendChild(ol);

                // load to TODOs, each into their own <li>
                let howMany = 5;
                for (let i = 0; i < howMany; i++) {
                    let li = document.createElement('li');
                    // Create our string using template literals to insert variables {$var}
                    // https://www.w3schools.com/js/js_string_templates.asp
                    let text = document.createTextNode(`${json[i].title} - ${json[i].completed}`);
                    li.appendChild(text);
                    ol.appendChild(li);
                }
            });
    };
};