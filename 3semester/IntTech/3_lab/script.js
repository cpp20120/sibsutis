class Currency {
  constructor(name, rate) {
      this.name = name;
      this.rate = rate;
  }
}

class ExpenseType {
  constructor(name) {
      this.name = name;
  }
}

class IncomeType {
  constructor(name) {
      this.name = name;
  }
}

class Expense {
  constructor(value, type, date) {
      this.value = value;
      this.type = type;
      this.date = date;
  }
}

class Income {
  constructor(value, type, date) {
      this.value = value;
      this.type = type;
      this.date = date;
  }
}

class Budget {
  constructor() {
      this.currencies = [];
      this.expenseTypes = [];
      this.incomeTypes = [];
      this.expenses = [];
      this.incomes = [];
  }

  addCurrency(currency) {
      this.currencies.push(currency);
  }

  updateCurrency(index, currency) {
      this.currencies[index] = currency;
  }

  deleteCurrency(index) {
      this.currencies.splice(index, 1);
  }

  addExpenseType(expenseType) {
      this.expenseTypes.push(expenseType);
  }

  updateExpenseType(index, expenseType) {
      this.expenseTypes[index] = expenseType;
  }

  deleteExpenseType(index) {
      this.expenseTypes.splice(index, 1);
  }

  addIncomeType(incomeType) {
      this.incomeTypes.push(incomeType);
  }

  updateIncomeType(index, incomeType) {
      this.incomeTypes[index] = incomeType;
  }

  deleteIncomeType(index) {
      this.incomeTypes.splice(index, 1);
  }

  addExpense(expense) {
      this.expenses.push(expense);
  }

  updateExpense(index, expense) {
      this.expenses[index] = expense;
  }

  deleteExpense(index) {
      this.expenses.splice(index, 1);
  }

  addIncome(income) {
      this.incomes.push(income);
  }

  updateIncome(index, income) {
      this.incomes[index] = income;
  }

  deleteIncome(index) {
      this.incomes.splice(index, 1);
  }

  calculateBalance(startDate, endDate) {
      let totalIncome = this.incomes
          .filter(income => income.date >= startDate && income.date <= endDate)
          .reduce((sum, income) => sum + parseFloat(income.value), 0);

      let totalExpense = this.expenses
          .filter(expense => expense.date >= startDate && expense.date <= endDate)
          .reduce((sum, expense) => sum + parseFloat(expense.value), 0);

      return totalIncome - totalExpense;
  }

  filterTransactions(startDate, endDate) {
      let filteredIncomes = this.incomes.filter(income => income.date >= startDate && income.date <= endDate);
      let filteredExpenses = this.expenses.filter(expense => expense.date >= startDate && expense.date <= endDate);

      return {
          incomes: filteredIncomes,
          expenses: filteredExpenses
      };
  }
}

let budget = new Budget();

function addCurrency() {
  let name = document.getElementById('currency-name').value;
  let rate = document.getElementById('currency-rate').value;
  let currency = new Currency(name, rate);
  budget.addCurrency(currency);
  updateCurrencyList();
}

function updateCurrency() {
  let index = prompt("Введите индекс валюты для обновления:");
  let name = document.getElementById('currency-name').value;
  let rate = document.getElementById('currency-rate').value;
  let currency = new Currency(name, rate);
  budget.updateCurrency(index, currency);
  updateCurrencyList();
}

function deleteCurrency() {
  let index = prompt("Введите индекс валюты для удаления:");
  budget.deleteCurrency(index);
  updateCurrencyList();
}

function updateCurrencyList() {
  let list = document.getElementById('currency-list');
  list.innerHTML = '';
  budget.currencies.forEach((currency, index) => {
      let li = document.createElement('li');
      li.textContent = `${index}: ${currency.name} - ${currency.rate}`;
      list.appendChild(li);
  });
}

function addExpenseType() {
  let name = document.getElementById('expense-type-name').value;
  let expenseType = new ExpenseType(name);
  budget.addExpenseType(expenseType);
  updateExpenseTypeList();
}

function updateExpenseType() {
  let index = prompt("Введите индекс типа расхода для обновления:");
  let name = document.getElementById('expense-type-name').value;
  let expenseType = new ExpenseType(name);
  budget.updateExpenseType(index, expenseType);
  updateExpenseTypeList();
}

function deleteExpenseType() {
  let index = prompt("Введите индекс типа расхода для удаления:");
  budget.deleteExpenseType(index);
  updateExpenseTypeList();
}

function updateExpenseTypeList() {
  let list = document.getElementById('expense-type-list');
  list.innerHTML = '';
  budget.expenseTypes.forEach((expenseType, index) => {
      let li = document.createElement('li');
      li.textContent = `${index}: ${expenseType.name}`;
      list.appendChild(li);
  });
}

function addIncomeType() {
  let name = document.getElementById('income-type-name').value;
  let incomeType = new IncomeType(name);
  budget.addIncomeType(incomeType);
  updateIncomeTypeList();
}

function updateIncomeType() {
  let index = prompt("Введите индекс типа дохода для обновления:");
  let name = document.getElementById('income-type-name').value;
  let incomeType = new IncomeType(name);
  budget.updateIncomeType(index, incomeType);
  updateIncomeTypeList();
}

function deleteIncomeType() {
  let index = prompt("Введите индекс типа дохода для удаления:");
  budget.deleteIncomeType(index);
  updateIncomeTypeList();
}

function updateIncomeTypeList() {
  let list = document.getElementById('income-type-list');
  list.innerHTML = '';
  budget.incomeTypes.forEach((incomeType, index) => {
      let li = document.createElement('li');
      li.textContent = `${index}: ${incomeType.name}`;
      list.appendChild(li);
  });
}

function addExpense() {
  let value = document.getElementById('expense-value').value;
  let type = document.getElementById('expense-type').value;
  let date = document.getElementById('expense-date').value;
  let expense = new Expense(value, type, date);
  budget.addExpense(expense);
  updateExpenseList();
}

function updateExpense() {
  let index = prompt("Введите индекс расхода для обновления:");
  let value = document.getElementById('expense-value').value;
  let type = document.getElementById('expense-type').value;
  let date = document.getElementById('expense-date').value;
  let expense = new Expense(value, type, date);
  budget.updateExpense(index, expense);
  updateExpenseList();
}

function deleteExpense() {
  let index = prompt("Введите индекс расхода для удаления:");
  budget.deleteExpense(index);
  updateExpenseList();
}

function updateExpenseList() {
  let list = document.getElementById('expense-list');
  list.innerHTML = '';
  budget.expenses.forEach((expense, index) => {
      let li = document.createElement('li');
      li.textContent = `${index}: ${expense.value} - ${expense.type} - ${expense.date}`;
      list.appendChild(li);
  });
}

function addIncome() {
  let value = document.getElementById('income-value').value;
  let type = document.getElementById('income-type').value;
  let date = document.getElementById('income-date').value;
  let income = new Income(value, type, date);
  budget.addIncome(income);
  updateIncomeList();
}

function updateIncome() {
  let index = prompt("Введите индекс дохода для обновления:");
  let value = document.getElementById('income-value').value;
  let type = document.getElementById('income-type').value;
  let date = document.getElementById('income-date').value;
  let income = new Income(value, type, date);
  budget.updateIncome(index, income);
  updateIncomeList();
}

function deleteIncome() {
  let index = prompt("Введите индекс дохода для удаления:");
  budget.deleteIncome(index);
  updateIncomeList();
}

function updateIncomeList() {
  let list = document.getElementById('income-list');
  list.innerHTML = '';
  budget.incomes.forEach((income, index) => {
      let li = document.createElement('li');
      li.textContent = `${index}: ${income.value} - ${income.type} - ${income.date}`;
      list.appendChild(li);
  });
}

function calculateBalance() {
  let startDate = document.getElementById('balance-start-date').value;
  let endDate = document.getElementById('balance-end-date').value;
  let balance = budget.calculateBalance(startDate, endDate);
  document.getElementById('balance-result').textContent = `Баланс: ${balance}`;
}

function filterTransactions() {
  let startDate = document.getElementById('filter-start-date').value;
  let endDate = document.getElementById('filter-end-date').value;
  let filtered = budget.filterTransactions(startDate, endDate);
  let list = document.getElementById('filter-result');
  list.innerHTML = '';
  filtered.incomes.forEach(income => {
      let li = document.createElement('li');
      li.textContent = `Доход: ${income.value} - ${income.type} - ${income.date}`;
      list.appendChild(li);
  });
  filtered.expenses.forEach(expense => {
      let li = document.createElement('li');
      li.textContent = `Расход: ${expense.value} - ${expense.type} - ${expense.date}`;
      list.appendChild(li);
  });
}