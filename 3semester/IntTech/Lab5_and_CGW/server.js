const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

const DATA_FILE = path.join(__dirname, 'budget.json');

app.use(bodyParser.json());
app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.use(express.static(path.join(__dirname, 'public')));

const readData = () => {
    try {
        if (!fs.existsSync(DATA_FILE)) {
            fs.writeFileSync(DATA_FILE, JSON.stringify({ incomes: [], expenses: [] }, null, 2));
        }
        const rawData = fs.readFileSync(DATA_FILE, 'utf-8');
        return JSON.parse(rawData);
    } catch (error) {
        console.error('Ошибка при чтении данных:', error);
        return { incomes: [], expenses: [] };
    }
};

const writeData = (data) => {
    try {
        fs.writeFileSync(DATA_FILE, JSON.stringify(data, null, 2));
        console.log('Данные успешно сохранены в файл.');
    } catch (error) {
        console.error('Ошибка при сохранении данных:', error);
    }
};

app.get('/api/budget', (req, res) => {
    try {
        const data = readData();
        res.json(data);
    } catch (error) {
        console.error('Ошибка при обработке GET-запроса:', error);
        res.status(500).json({ message: 'Ошибка при чтении данных', error });
    }
});

app.post('/api/budget', (req, res) => {
    try {
        const data = req.body;

        if (!data || !Array.isArray(data.incomes) || !Array.isArray(data.expenses)) {
            return res.status(400).json({ message: 'Неверный формат данных' });
        }

        writeData(data);
        res.status(200).json({ message: 'Данные успешно сохранены' });
    } catch (error) {
        console.error('Ошибка при обработке POST-запроса:', error);
        res.status(500).json({ message: 'Ошибка при сохранении данных', error });
    }
});

app.listen(PORT, (error) => {
    if (error) {
        console.error(`Ошибка при запуске сервера на порту ${PORT}:`, error);
    } else {
        console.log(`Сервер запущен на http://localhost:${PORT}`);
    }
});
