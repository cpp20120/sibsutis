class Currency {
  /**
   * Создает новый объект валюты
   * @param {string} name - название валюты
   */
  constructor(name) {
    this.name = name;
    this.rates = []; // массив объектов CurrencyRate
  }

  /**
   * Добавляет новый курс валюты
   * @param {string} date - дата, на которую установлен курс
   * @param {number} buyRate - курс покупки
   * @param {number} sellRate - курс продажи
   */
  addRate(date, buyRate, sellRate) {
    this.rates.push(new CurrencyRate(date, buyRate, sellRate));
  }

  /**
   * Ищет курс валюты по указанной дате
   * @param {string} date - дата, для которой нужно найти курс
   * @returns {CurrencyRate|null} - объект CurrencyRate, если курс найден, null - если не найден
   */
  getRateByDate(date) {
    return this.rates.find(rate => rate.date === date);
  }
}

class CurrencyRate {
  /**
   * Создает новый объект курса валюты
   * @param {string} date - дата, на которую установлен курс
   * @param {number} buyRate - курс покупки
   * @param {number} sellRate - курс продажи
   */
  constructor(date, buyRate, sellRate) {
    this.date = date;
    this.buyRate = buyRate;
    this.sellRate = sellRate;
  }
}

class Transaction {
  /**
   * Создает новый объект транзакции
   * @param {number} value - значение транзакции
   * @param {string} type - тип транзакции ('income' или 'expense')
   * @param {string} date - дата транзакции
   */
  constructor(value, type, date) {
    this.value = value;
    this.type = type; // 'income' или 'expense'
    this.date = date;
    this.typeName = ''; // тип дохода или расхода
  }
}

class Budget {
  /**
   * Создает новый объект бюджета
   * @constructor
   */
  constructor() {
    this.currencies = [];
    this.expenseTypes = [];
    this.incomeTypes = [];
    this.transactions = [];
  }

  /**
   * Добавляет валюту к бюджету
   * @param {Currency} currency - объект валюты
   */
  addCurrency(currency) {
    this.currencies.push(currency);
  }

  /**
   * Добавляет тип расхода к бюджету
   * @param {string} type - тип расхода
   */
  addExpenseType(type) {
    this.expenseTypes.push(type);
  }

  /**
   * Добавляет тип дохода к бюджету
   * @param {string} type - тип дохода
   */
  addIncomeType(type) {
    this.incomeTypes.push(type);
  }

  /**
   * Добавляет транзакцию к бюджету
   * @param {Transaction} transaction - объект транзакции
   */
  addTransaction(transaction) {
    this.transactions.push(transaction);
  }

  /**
   * Возвращает баланс доходов и расходов за указанный период
   * @param {string} startDate - начальная дата периода (включительно)
   * @param {string} endDate - конечная дата периода (включительно)
   * @returns {number} баланс доходов и расходов
   */
  getBalance(startDate, endDate) {
    const start = new Date(startDate);
    const end = new Date(endDate);
    const filteredTransactions = this.transactions.filter(t => {
      const transactionDate = new Date(t.date);
      return transactionDate >= start && transactionDate <= end;
    });
    // Подсчет баланса
    let balance = 0;
    filteredTransactions.forEach(t => {
      balance += t.type === 'income' ? t.value : -t.value;
    });

    return balance;
  }

  /**
   Возвращает массив транзакций, отфильтрованных по типу, дате и названию типа
   * @param {string} type - тип транзакции ("доход" или "расход")
   * @param {string} StartDate - дата начала периода (включительно)
   * @param {строка} EndDate - дата окончания периода (включительно)
   * @param {строка} filter Type - название типа, по которому будет производиться фильтрация
   * @returns {Array<Transaction>} отфильтрованные транзакции
   */
  filterTransactions(type, startDate, endDate, filterType) {
    const start = new Date(startDate);
    const end = new Date(endDate);
    // Фильтрация транзакции
    return this.transactions.filter(t => {
      const transactionDate = new Date(t.date);
      return (
        t.type === type &&
        transactionDate >= start &&
        transactionDate <= end &&
        t.typeName === filterType
      );
    });
  }

  /**
   * Удаляет транзакцию из бюджета
   * @param {number} id - id транзакции, которую нужно удалить
   */
  removeTransaction(id) {
    const index = this.transactions.findIndex(t => t.id === id);
    if (index !== -1) {
      this.transactions.splice(index, 1);
    }
  }
}

const budget = new Budget();

/**
 * Добавляет валюту к бюджету
 */
document.getElementById("currency-form").addEventListener("submit", event => {
  event.preventDefault();
  const name = document.getElementById("currency-name").value;
  const date = document.getElementById("currency-rate-date").value;
  const buyRate = parseFloat(document.getElementById("currency-buy-rate").value);
  const sellRate = parseFloat(document.getElementById("currency-sell-rate").value);

  const currency = new Currency(name);
  currency.addRate(date, buyRate, sellRate);
  budget.addCurrency(currency);

  const listItem = document.createElement("li");
  listItem.textContent = `${name} - Курс на ${date}: Покупка ${buyRate}, Продажа ${sellRate}`;
  document.getElementById("currency-list").appendChild(listItem);
});

/**
 * Добавляет тип расхода к бюджету
 */
document.getElementById("expense-type-form").addEventListener("submit", event => {
  event.preventDefault(); // предотвращает отправку формы
  const name = document.getElementById("expense-type-name").value;
  budget.addExpenseType(name);
  
  const listItem = document.createElement("li");
  listItem.textContent = name;
  document.getElementById("expense-type-list").appendChild(listItem);
  
  const option = document.createElement("option");
  option.value = name;
  option.textContent = name;
  document.getElementById("filter-type").appendChild(option);
});

/**
 * Добавляет тип дохода к бюджету
 */
document.getElementById("income-type-form").addEventListener("submit", event => {
  event.preventDefault();
  const name = document.getElementById("income-type-name").value;
  budget.addIncomeType(name);
  
  const listItem = document.createElement("li");
  listItem.textContent = name;
  document.getElementById("income-type-list").appendChild(listItem);
  
  const option = document.createElement("option");
  option.value = name;
  option.textContent = name;
  document.getElementById("filter-type").appendChild(option);
});

/**
 * Добавляет транзакцию к бюджету
 */
document.getElementById("transaction-form").addEventListener("submit", event => {
  event.preventDefault();
  const value = parseFloat(document.getElementById("transaction-value").value);
  const type = document.getElementById("transaction-type").value;
  const date = document.getElementById("transaction-date").value;
  const typeName = document.getElementById("filter-type").value;
  
  const transaction = new Transaction(value, type, date);
  transaction.typeName = typeName;
  budget.addTransaction(transaction);
  
  const listItem = document.createElement("li");
  listItem.textContent = `${type === 'income' ? 'Доход' : 'Расход'}: ${value} на ${date} (${typeName})`;
  document.getElementById("transaction-list").appendChild(listItem);
});

/**
 * Удаляет транзакцию из бюджета
 */
document.getElementById("transaction-list").addEventListener("click", event => {
  if (event.target.tagName === "BUTTON") {
    const id = parseInt(event.target.getAttribute("data-id"));
    budget.removeTransaction(id);
    event.target.parentNode.remove();
  }
});

/**
 * Получает баланс за период
 */
document.getElementById("balance-form").addEventListener("submit", event => {
  event.preventDefault();
  const startDate = document.getElementById("balance-start-date").value;
  const endDate = document.getElementById("balance-end-date").value;
  
  const balance = budget.getBalance(startDate, endDate);
  document.getElementById("balance-result").textContent = `Баланс за период: ${balance}`;
});

/**
 * Фильтрует транзакции
 */
document.getElementById("filter-form").addEventListener("submit", event => {
  event.preventDefault();
  const type = document.getElementById("filter-transaction-type").value;
  const filterType = document.getElementById("filter-type").value;
  const startDate = document.getElementById("filter-start-date").value;
  const endDate = document.getElementById("filter-end-date").value;

  // Получение результатов фильтрации
  const results = budget.filterTransactions(type, startDate, endDate, filterType);

  // Обновление списка результатов
  const resultList = document.getElementById("filter-result");
  resultList.innerHTML = ""; // Очистка предыдущих результатов

  if (results.length === 0) {
    const listItem = document.createElement("li");
    listItem.textContent = "Нет транзакций за указанный период.";
    resultList.appendChild(listItem);
  } else {
    results.forEach(t => {
      const listItem = document.createElement("li");
      listItem.textContent = `${type === 'income' ? 'Доход' : 'Расход'}: ${t.value} на ${t.date} (${t.typeName})`;
      resultList.appendChild(listItem);
    });
  }

  // Обновление баланса
  const balance = budget.getBalance(startDate, endDate);
  document.getElementById("balance-result").textContent = `Баланс за период: ${balance}`;
  console.log(balance);
});
