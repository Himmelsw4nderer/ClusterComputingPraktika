from flask import Flask, request, jsonify

app = Flask(__name__)

# Datenstruktur, um Geldbestände zu speichern
balances = {
    "EUR": 1000,
    "USD": 500,
    "GBP": 300,
    "CHF": 200
}

# Fest kodierter Wechselkurs
exchange_rates = {
    "EUR": 1.0,
    "USD": 1.12,
    "GBP": 0.85,
    "CHF": 1.07
}

@app.route('/balances', methods=['GET'])
def get_balances():
    return jsonify(balances)

@app.route('/deposit/<currency>/<amount>', methods=['POST'])
def deposit(currency, amount):
    if currency in balances:
        balances[currency] += float(amount)
    else:
        return "Unsupported currency", 400
    return jsonify({currency: balances[currency]})

@app.route('/withdraw/<currency>/<amount>', methods=['POST'])
def withdraw(currency, amount):
    if currency in balances:
        if balances[currency] >= float(amount):
            balances[currency] -= float(amount)
            return jsonify({currency: balances[currency]})
        else:
            return "Not enough balance", 400
    else:
        return "Unsupported currency", 400

@app.route('/total_value/<currency>', methods=['GET'])
def total_value(currency):
    if currency in exchange_rates:
        total_value = sum(balances[c] / exchange_rates[currency] * exchange_rates[c] for c in balances)
        return jsonify({"Total Value": total_value})
    else:
        return "Unsupported currency", 400

if __name__ == '__main__':
    app.run(debug=True)
