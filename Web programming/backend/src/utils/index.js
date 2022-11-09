const validator = require('validator');
const nodemailer = require('nodemailer');
const { Pool } = require('pg');

const validateFields = (fields) => {

    for (let fieldName in fields) {
        const fieldValue = fields[fieldName].value + ''; // validator functioneaza doar pe strings
        const fieldType = fields[fieldName].type;

        if (!fieldValue) {
            throw new ServerError(`Lipseste campul ${fieldName}`, 400);
        }

        switch (fieldType) {
            case 'ascii':
                if (!validator.isAscii(fieldValue)) {
                    throw new Error(`Campul ${fieldName} trebuie sa contina doar caractere ascii`);
                }
                break;
            case 'alpha':
                if (!validator.isAlpha(fieldValue)) {
                    throw new Error(`Campul ${fieldName} trebuie sa contina doar litere`);
                }
                break;
            case 'int':
                if (!validator.isInt(fieldValue)) {
                    throw new Error(`Campul ${fieldName} trebuie sa fie un numar intreg`);
                }
                break;
            case 'jwt':
                if (!validator.isJWT(fieldValue)) {
                    throw new Error(`Campul ${fieldName} trebuie sa fie jwt`);
                }
                break;
        }
    }

}
const transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: "voiculescuidaux@gmail.com",      // generated ethereal user
        pass: "Demo_mec"                        // generated ethereal password
    }
});

const key = '74710c44-8b19-4174-b67c-681adaeb98c3';

const pool = new Pool({
    user: 'docker',
    host: 'postgre',
    database: 'docker',
    password: 'docker',
    port: 5432,
})

const query = async (text, params) => {
    const start = Date.now();
    const {
        rows,
    } = await pool.query(text, params);
    const duration = Date.now() - start;
    console.log(`Query took ${duration} and returned ${rows.length} rows.`);
    return rows;
};

module.exports = {
    query,
    validateFields,
    transporter,
    key
}
