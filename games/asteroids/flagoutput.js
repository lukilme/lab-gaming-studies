const outputElement = document.getElementById("output");
// Redireciona stdout
var Module = {
    print: function (text) {
        outputElement.innerText += text + "\n";
    },
    printErr: function (text) {
        outputElement.innerText += "[Error] " + text + "\n";
    }
};