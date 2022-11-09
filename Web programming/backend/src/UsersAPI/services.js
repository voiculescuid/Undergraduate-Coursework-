var passwordHash = require('password-hash');
var jwt = require('jsonwebtoken');

const { query, key } = require('../utils');

const getUsers = async () => {
    return await query('SELECT * FROM users');
};

const add = async (name, username, email, password, role_id) => {
    let passwordDigest = passwordHash.generate(password);
    return await query(`INSERT INTO users (name, username, email, password, role_id) VALUES ($1, $2, $3, $4, $5)`, [name, username, email, passwordDigest, role_id]);
};

const authenticate = async (username, password) => {
    const result = await query(`SELECT u.id, u.password, r.value as role FROM users u 
                                JOIN roles r ON r.id = u.role_id
                                WHERE u.username = $1`, [username]);
    if (result.length === 0) {
        throw new Error(`Utilizatorul ${username} nu exista!`);
    }
    const user = result[0];

    if (passwordHash.isHashed(user['password'])) {
        if (!passwordHash.verify(password, user['password'])) {
            throw new Error(`Parola gresita!`);
        }
    }
    else {
        if (!password === user['password']) {
            throw new Error(`Parola gresita!`);
        }
    }

    credentials = {
        token: jwt.sign({ 'user': user['id'], 'role': user['role'] }, key),
        role: user['role']
    };

    return credentials;
};

module.exports = {
    add,
    getUsers,
    authenticate
}