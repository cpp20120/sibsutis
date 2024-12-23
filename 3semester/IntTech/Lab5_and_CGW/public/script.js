class Currency {
  constructor(options) {
    this.name = options.name;
    this._Rate = {};
  }

  set Rate(options) {
    this._Rate[options.date] = options.rate;
  }

  Update(options) {
    if (options.name) this.name = options.name;
  }
}

class ExpenseType {
  constructor(options) {
    this.name = options.name;
  }

  Update(options) {
    if (options.name) this.name = options.name;
  }
}

class IncomeType {
  constructor(options) {
    this.name = options.name;
  }

  Update(options) {
    if (options.name) this.name = options.name;
  }
}

class Expense {
  constructor(options) {
    this.value = options.value;
    this.type = options.type;
    this.date = options.date;
    this.currency = options.currency; //
  }

  Update(options) {
    if (options.value) this.value = options.value;
    if (options.type) this.type = options.type;
    if (options.date) this.date = options.date;
    if (options.currency) this.currency = options.currency;
  }
}

class Income {
  constructor(options) {
    this.value = options.value;
    this.type = options.type;
    this.date = options.date;
    this.currency = options.currency;
  }

  Update(options) {
    if (options.value) this.value = options.value;
    if (options.type) this.type = options.type;
    if (options.date) this.date = options.date;

    if (options.currency) this.currency = options.currency;
  }
}

document.addEventListener("DOMContentLoaded", () => {
  loadBudgetFromServer();
});

class Budget {
  constructor() {
    this.currencyArray = [];
    this.expenseTypeArray = [];
    this.incomeTypeArray = [];
    this.incomeArray = [];
    this.expenseArray = [];
    this.tableBody = document.querySelector("#incomeTable tbody");
    this.tableBodyE = document.querySelector("#expenseTable tbody");
    this.editingIndex = null;
    this.editingIndexE = null;
  }

  createCurrency(options) {
    const currency = new Currency(options);
    this.currencyArray.push(currency);
    return currency.name;
  }

  createExpenseType(options) {
    const expenseType = new ExpenseType(options);
    this.expenseTypeArray.push(expenseType);
  }

  createIncomeType(options) {
    const incomeType = new IncomeType(options);
    this.incomeTypeArray.push(incomeType);
  }

  createExpense(options) {
    const expense = new Expense(options);
    this.expenseArray.push(expense);
  }

  createIncome(options) {
    const income = new Income(options);
    this.incomeArray.push(income);
  }

  readCurrency(name) {
    return this.currencyArray.find((currency) => currency.name === name);
  }

  readExpenseType(name) {
    return this.expenseTypeArray.find(
      (expenseType) => expenseType.name === name
    );
  }

  readIncomeType(name) {
    return this.incomeTypeArray.find((incomeType) => incomeType.name === name);
  }

  readExpense(date) {
    return this.expenseArray.filter(
      (expense) => expense.date.toDateString() === new Date(date).toDateString()
    );
  }

  readIncome(date) {
    return this.incomeArray.filter(
      (income) => income.date.toDateString() === new Date(date).toDateString()
    );
  }

  updateCurrency(name, options) {
    const currency = this.readCurrency(name);

    if (currency) currency.Update(options);
  }

  updateExpenseType(name, options) {
    const expenseType = this.readExpenseType(name);

    if (expenseType) expenseType.Update(options);
  }

  updateIncomeType(name, options) {
    const incomeType = this.readIncomeType(name);

    if (incomeType) incomeType.Update(options);
  }

  updateExpense(id, options) {
    const expense = this.expenseArray[id];

    if (expense) expense.Update(options);
  }

  updateIncome(id, options) {
    const income = this.incomeArray[id];

    if (income) income.Update(options);
  }

  deleteCurrency(name) {
    this.currencyArray = this.currencyArray.filter(
      (currency) => currency.name !== name
    );
  }

  deleteExpenseType(name) {
    this.expenseTypeArray = this.expenseTypeArray.filter(
      (expenseType) => expenseType.name !== name
    );
  }

  deleteIncomeType(name) {
    this.incomeTypeArray = this.incomeTypeArray.filter(
      (incomeType) => incomeType.name !== name
    );
  }

  deleteExpense(id) {
    this.expenseArray = this.expenseArray.filter(
      (expense, index) => index !== id
    );
  }

  deleteIncome(id) {
    this.incomeArray = this.incomeArray.filter((income, index) => index !== id);
  }

  loadFromJSON(data) {

    let i;
    for (i = 0; i < data.incomes.length; i++) {
      this.createIncome({
        value: data.incomes[i].value,
        type: data.incomes[i].type,
        date: data.incomes[i].date,
        currency: data.incomes[i].currency
      });

      const row = document.createElement("tr");
      row.innerHTML = `
                <td id = "iVl">${data.incomes[i].value}</td>
                <td id = "iTp">${data.incomes[i].type}</td>
                <td id = "iDt">${data.incomes[i].date}</td>
                <td id = "iCr">${data.incomes[i].currency}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditIncome(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteIncome(this)">Удалить</button>
                </td>
            `;

      this.tableBody.appendChild(row);
    }

    for (i = 0; i < data.expenses.length; i++) {
      this.createExpense({
        value: data.expenses[i].value,
        type: data.expenses[i].type,
        date: data.expenses[i].date,
        currency: data.expenses[i].currency,
      });

      const rowE = document.createElement("tr");
      rowE.innerHTML = `
                <td>${data.expenses[i].value}</td>
                <td>${data.expenses[i].type}</td>
                <td>${data.expenses[i].date}</td>
                <td>${data.expenses[i].currency}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditExpense(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteExpense(this)">Удалить</button>
                </td>
            `;

      this.tableBodyE.appendChild(rowE);
    }

  }

  balance(startDate, endDate, filterType = null) {
    let globalIncome = 0;
    let globalExpense = 0;

    let sum1 = 0;
    let sum2 = 0;

    const filteredIncomes = this.incomeArray.filter(
      (income) =>
        income.date >= startDate && income.date <= endDate
    );
    const filteredExpenses = this.expenseArray.filter(
      (expense) =>
        expense.date >= startDate && expense.date <= endDate
    );

    if (filterType) {
      globalIncome = filteredIncomes
        .filter((income) => income.type.name === filterType)
        .reduce((sum, income) => sum + income.value, 0);
      globalExpense = filteredExpenses
        .filter((expense) => expense.type.name === filterType)
        .reduce((sum, expense) => sum + expense.value, 0);
    } else {
      globalIncome = filteredIncomes.reduce(
        (sum, income) => +sum + +income.value,
        0
      );
      globalExpense = filteredExpenses.reduce(
        (sum, expense) => +sum + +expense.value,
        0
      );
    }

    return globalIncome - globalExpense;
  }

  filter(startDate, endDate, filterType = null, isIncome = true) {
    const entries = isIncome ? this.incomeArray : this.expenseArray;

    return entries.filter(
      (entry) =>
        entry.date >= startDate &&
        entry.date <= endDate &&
        (!filterType || entry.type === filterType)
    );
  }

  addIncome(value, type, date, currency) {
    if (this.editingIndex !== null) {
      this.updateIncome(this.editingIndex, {
        value: value,
        type: type,
        date: date,
        currency: this.readCurrency(currency),
      });

      const row = this.tableBody.children[this.editingIndex];

      const income = document.createElement("tr");
      income.innerHTML = `
                <td>${value}</td>
                <td>${type}</td>
                <td>${date}</td>
                <td>${currency}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditIncome(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteIncome(this)">Удалить</button>
                </td>
            `;

      row.replaceWith(income);
      this.editingIndex = null;
    } else {
      const curname = this.createCurrency({ name: currency });
      this.createIncome({
        value: value,
        type: type,
        date: date,
        currency: curname,
      });
      const row = document.createElement("tr");
      row.innerHTML = `
                <td id = "iVl">${value}</td>
                <td id = "iTp">${type}</td>
                <td id = "iDt">${date}</td>
                <td id = "iCr">${curname}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditIncome(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteIncome(this)">Удалить</button>
                </td>
            `;

      this.tableBody.appendChild(row);
    }
    saveBudgetToServer();
  }

  editIncome(row) {
    const index = Array.from(this.tableBody.children).indexOf(row);

    if (index > -1) {
      this.editingIndex = index;

      //Заполнение формы значениями редактируемой записи
      document.getElementById("incomeValue").value =
        this.incomeArray[this.editingIndex].value;
      document.getElementById("incomeType").value =
        this.incomeArray[this.editingIndex].type.name;
      document.getElementById("incomeCurrency").value =
        this.incomeArray[this.editingIndex].currency;
    }
    saveBudgetToServer();
  }

  removeIncome(row) {
    const index = Array.from(this.tableBody.children).indexOf(row);
    if (index > -1) {
      this.deleteIncome(index);
      this.tableBody.removeChild(row);
    }
    saveBudgetToServer();
  }

  addExpense(value, type, date, currency) {
    if (this.editingIndexE !== null) {
      this.updateExpense(this.editingIndexE, {
        value: value,
        type: type,
        date: date,
        currency: this.readCurrency(currency),
      });

      const row = this.tableBodyE.children[this.editingIndexE];

      const expense = document.createElement("tr");
      expense.innerHTML = `
                <td>${value}</td>
                <td>${type}</td>
                <td>${date}</td>
                <td>${currency}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditExpense(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteExpense(this)">Удалить</button>
                </td>
            `;

      row.replaceWith(expense);
      this.editingIndexE = null;
    } else {
      const curname = this.createCurrency({ name: currency });
      this.createExpense({
        value: value,
        type: type,
        date: date,
        currency: curname,
      });
      const row = document.createElement("tr");
      row.innerHTML = `
                <td>${value}</td>
                <td>${type}</td>
                <td>${date}</td>
                <td>${curname}</td>
                <td>
                    <button class="btn btn-success" onclick="handleEditExpense(this)">Редактировать</button>
                    <button class="btn btn-success" onclick="handleDeleteExpense(this)">Удалить</button>
                </td>
            `;

      this.tableBodyE.appendChild(row);
    }
    saveBudgetToServer();
  }

  editExpense(row) {
    const index = Array.from(this.tableBodyE.children).indexOf(row);

    if (index > -1) {
      this.editingIndexE = index;

      //Заполнение формы значениями редактируемой записи
      document.getElementById("expenseValue").value =
        this.expenseArray[this.editingIndexE].value;
      document.getElementById("expenseType").value =
        this.expenseArray[this.editingIndexE].type.name;
      document.getElementById("expenseCurrency").value =
        this.expenseArray[this.editingIndexE].currency;
    }
    saveBudgetToServer();
  }

  removeExpense(row) {
    const index = Array.from(this.tableBodyE.children).indexOf(row);
    if (index > -1) {
      this.deleteExpense(index);
      this.tableBodyE.removeChild(row);
    }
    saveBudgetToServer();
  }
}



const myBudget = new Budget();

async function loadBudgetFromServer() {
  try {
    const response = await fetch("/api/budget");
    if (!response.ok) throw new Error("Ошибка загрузки данных с сервера.");

    const budgetData = await response.json();
    myBudget.loadFromJSON(budgetData); // Восстанавливаем объект бюджета
  } catch (error) {
    console.error("Не удалось загрузить данные бюджета:", error);
  }
}

async function saveBudgetToServer() {
  const budgetData = {
    incomes: myBudget.incomeArray,
    expenses: myBudget.expenseArray,
  };

  const response = await fetch("/api/budget", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(budgetData),
  });

  if (!response.ok) {
    console.error("Не удалось сохранить данные бюджета.");
  }
}

function handleAddIncome() {
  const value = document.getElementById("incomeValue").value;
  const type = document.getElementById("incomeType").value;
  const date = document.getElementById("incomeDate").value;
  const currency = document.getElementById("incomeCurrency").value;

  if (value && type && date && currency) {
    myBudget.addIncome(value, type, date, currency);

    // Очистка формы
    document.getElementById("incomeValue").value = "";
    document.getElementById("incomeType").value = "";
    document.getElementById("incomeDate").value = "";
    document.getElementById("incomeCurrency").value = "";
  } else {
    alert("Ошибка. Не все поля заполнены.");
  }
}

function handleEditIncome(button) {
  const row = button.parentElement.parentElement;
  myBudget.editIncome(row);
}

function handleDeleteIncome(button) {
  const row = button.parentElement.parentElement;
  myBudget.removeIncome(row);
}

function handleAddExpense() {
  const value = document.getElementById("expenseValue").value;
  const type = document.getElementById("expenseType").value;
  const date = document.getElementById("expenseDate").value;
  const currency = document.getElementById("expenseCurrency").value;

  if (value && type && date && currency) {
    myBudget.addExpense(value, type, date, currency);

    // Очистка формы
    document.getElementById("expenseValue").value = "";
    document.getElementById("expenseType").value = "";
    document.getElementById("expenseDate").value = "";
    document.getElementById("expenseCurrency").value = "";
  } else {
    alert("Ошибка. Не все поля заполнены.");
  }
}

function handleEditExpense(button) {
  const row = button.parentElement.parentElement;
  myBudget.editExpense(row);
}

function handleDeleteExpense(button) {
  const row = button.parentElement.parentElement;
  myBudget.removeExpense(row);
}

function printBalance() {
  const startDate = document.getElementById("startDate").value;
  const endDate = document.getElementById("endDate").value;

  if (startDate && endDate) {
    const balance = myBudget.balance(startDate, endDate);

    document.getElementById("balanceNumber").innerHTML = balance;

    document.getElementById("startDate").value = "";
    document.getElementById("endDate").value = "";
  } else {
    alert("Ошибка. Не все поля заполнены.");
  }
}

function printFilter() {
  const startDate = document.getElementById("stDate").value;
  const endDate = document.getElementById("enDate").value;
  const inType = document.getElementById("inType").value;
  const exType = document.getElementById("exType").value;

  if (startDate && endDate && inType && exType) {
    const filterIn = myBudget.filter(startDate, endDate, inType, true);
    const filterEx = myBudget.filter(startDate, endDate, exType, false);

    var i;
    let sumIn = 0;
    for (i = 0; i < filterIn.length; i++) {
      sumIn = +sumIn + +filterIn[i].value;
    }

    let sumEx = 0;
    for (i = 0; i < filterEx.length; i++) {
      sumEx = +sumEx + +filterEx[i].value;
    }

    document.getElementById("filterIn").innerHTML = sumIn;
    document.getElementById("filterEx").innerHTML = sumEx;

    document.getElementById("stDate").value = "";
    document.getElementById("enDate").value = "";
    document.getElementById("inType").value = "";
    document.getElementById("exType").value = "";

    let tbody = document.querySelector("#incomeTableFilter tbody");
    tbody.innerHTML = `<tr>
                         <th>Значение</th>
                         <th>Дата</th>
                         <th>Валюта</th>
                       </tr>`;
    myBudget.incomeArray.forEach((income, index) => {
      const tr = document.createElement("tr");
      tr.innerHTML = `<td>${income.value}</td>
                      <td>${income.date}</td>
                      <td>${income.currency}</td>`;
      tbody.appendChild(tr);
    });

    tbody = document.querySelector("#expenseTableFilter tbody");
    tbody.innerHTML = `<tr>
                         <th>Значение</th>
                         <th>Дата</th>
                         <th>Валюта</th>
                       </tr>`;
    myBudget.expenseArray.forEach((expense, index) => {
      const tr = document.createElement("tr");
      tr.innerHTML = `<td>${expense.value}</td>
                      <td>${expense.date}</td>
                      <td>${expense.currency}</td>`;
      tbody.appendChild(tr);
    });
  } else {
    alert("Ошибка. Не все поля заполнены.");
  }
}



let myChart;
function showChart() {
  const inar = myBudget.incomeArray.map((e) => e.date);
  const exar = myBudget.expenseArray.map((e) => e.date);

  const data = [...inar, ...exar];

  let i;
  let j;

  for (i = 0; i < data.length; i++) {
    for (j = data.length - 1; j > i; j--) {
      if (data[j - 1] > data[j]) {
        const temp = data[j - 1];
        data[j - 1] = data[j];
        data[j] = temp;
      }
    }
  }

  const labels = Array.from(new Set(data));

  let k = 0;
  for (k; k < labels.length; k++) {
    console.log(labels[k]);
  }

  const balances = [];

  let bal;
  let ii = 0;
  for (ii; ii < data.length; ii++) {
    bal = myBudget.balance(data[ii], data[ii]);
    balances.push(bal);
    console.log(balances[ii]);
  }

  const nbalances = Array.from(new Set(balances));

  for (ii = 0; ii < nbalances.length; ii++) {
    console.log(nbalances[ii]);
  }


  const ctx = document.getElementById("myChart");
  if (myChart) myChart.destroy();

  myChart = new Chart(ctx, {
    type: "line",
    data: {
      labels: [],
      datasets: [
        {
          data: [],
          lineTension: 0,
          backgroundColor: "transparent",
          borderColor: "#04935a",
          borderWidth: 5,
          pointBackgroundColor: "#04935a",
        },
      ],
    },
    options: {
      plugins: {
        legend: {
          display: false,
        },
        tooltip: {
          boxPadding: 5,
        },
      },
      scales: {
        x: {
          title: {
            display: true,
            text: "Дата",
          },
        },
        y: {
          title: {
            display: true,
            text: "Значение баланса",
          },
          beginAtZero: true,
        },
      },
    },
  });

  myChart.data.labels = labels;
  myChart.data.datasets[0].data = nbalances;

  myChart.update();
}
