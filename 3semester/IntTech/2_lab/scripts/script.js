let num = 42;
let str = "Привет";
let bool = true;
let empty = null;
let notDefined;
let obj = {};

const NUM = 42;
const STR = "Привет";
const BOOL = true;
const EMPTY = null;
const NOTDefined = undefined;
const Obj = {};

function checkAvailability() {
    const output = document.getElementById('output');
    output.innerHTML += "<p>Переменная localNum, определенная в mainFunction - " + (typeof localNum !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Константа localStr, определенная в mainFunction - " + (typeof localStr !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Переменная num, определенная в документе - " + (typeof num !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Константа str, определенная в документе - " + (typeof str !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Переменная bool, определенная в документе - " + (typeof bool !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Переменная empty, определенная в документе - " + (typeof empty !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Переменная notDefined, определенная в документе - " + (typeof notDefined !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Константа obj, определенная в документе - " + (typeof obj !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";

    output.style.backgroundImage = "url('/image/1.jpg') !important";
}


function otherFunction() {
    const output = document.getElementById('output');

    output.innerHTML += "<p>Переменная localNum, определенная в mainFunction - " + (typeof localNum !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Константа localStr, определенная в mainFunction - " + (typeof localStr !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Переменная num, определенная в документе - " + (typeof num !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";
    output.innerHTML += "<p>Константа str, определенная в документе - " + (typeof str !== 'undefined' ? "Доступна" : "Не доступна") + "</p>";

    output.style.backgroundImage = "url('/image/1.jpg') !important";
}

function mainFunction() {
    let localNum = 100;
    const localStr = "Локальная строка";


    otherFunction();
}
function typeConversionExamples() {
    let number = "5";

    const output = document.getElementById('output');

    output.innerHTML += "<p>Строка '5' + 5 = " + (number + 5) + "</p>";
    output.innerHTML += "<p>Строка '5' превращается в число: +number = " + (+number) + "</p>";

    let a = 5;
    output.innerHTML += "<p>++a = " + (++a) + "</p>";

    let b = 5;
    output.innerHTML += "<p>a++ = " + (b++) + ", после: a = " + (b) + "</p>";

    output.style.backgroundImage = "url('/image/1.jpg') !important";
}

function userInteraction() {
    alert("Это сообщение через alert!");
    const name = prompt("напиши что-то");
    const confirmation = confirm("точно??");

    const output = document.getElementById('output');
    output.innerHTML += "<p>То что написал пользователь: " + name + "</p>";
    output.innerHTML += "<p>Пользователь уверен: " + (confirmation ? "Да" : "Нет") + "</p>";

    output.style.backgroundImage = "url('/image/1.jpg') !important";
}

function loopsAndSwitchExample() {
    const output = document.getElementById('output');

    output.innerHTML += `<p>Цикл for:</p>`;
    for (let i = 1; i <= 5; i++) {
        output.innerHTML += `<p>Итерация ${i}</p>`;
    }


    let arg = prompt("Введите цифру?(от 0 до 1)");
    switch (arg) {
        case '0': case '1':
            alert('Один или ноль');
            break;

        case '2':
            alert('Два');
            break;

        default:
            alert('Попробуй еще раз.');
    }

}

const functionExpressionExample = function () {
    const output = document.getElementById('output');
    output.innerHTML += `<p>Это пример функции, созданной через Function Expression</p>`;
};

checkAvailability();
typeConversionExamples();
userInteraction();
loopsAndSwitchExample();
mainFunction();
functionExpressionExample();