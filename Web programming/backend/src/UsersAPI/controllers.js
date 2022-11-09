const express = require('express');
const jwt = require('jsonwebtoken');
const { validateFields, transporter, key } = require('../utils');

const UsersService = require('./services.js');
const router = express.Router();

router.post('/signup', async (req, res) => {
    const {
        name,
        username,
        email,
        password
    } = req.body;

    try {
        const fieldsToBeValidated = {
            name: {
                value: name,
                type: 'ascii'
            },
            username: {
                value: username,
                type: 'alpha'
            },
            email: {
                value: email,
                type: 'ascii'
            },
            password: {
                value: password,
                type: 'ascii'
            }
        };

        validateFields(fieldsToBeValidated);

        // role_id = 1 Administrator
        // role_id = 2 User

        let token = jwt.sign({name, username, email, password, role_id: 2 }, key);
        let activateUrl = "http://localhost:12000/users/" + token;

        var mailOptions = {
            from: `Voiculescu Ion-Daniel <voiculescuidaux@gmail.com>`,  // sender address
            to: `${name} <${email}>`,                                   // list of receivers
            subject: `Activate account`,                                // Subject line
            text: activateUrl,                                          // plain text body
        };

        transporter.sendMail(mailOptions, function (error, info) {
            if (error) {
                console.log(error);
                res.status(403).end();
            } else {
                console.log('Email sent: ' + info.response);
                res.status(201).end();
            }
        });
    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
});


router.get('/:token', async (req, res) => {
    let decode = jwt.decode(req.params.token, key);


    try {

        const {
            name,
            username,
            password,
            email,
            role_id
        } = decode;

        const fieldsToBeValidated = {
            name: {
                value: name,
                type: 'ascii'
            },
            username: {
                value: username,
                type: 'alpha'
            },
            email: {
                value: email,
                type: 'ascii'
            },
            password: {
                value: password,
                type: 'ascii'
            },
            role_id: {
                value: role_id,
                type: 'int'
            }
        };

        validateFields(fieldsToBeValidated);

        await UsersService.add(name, username, email, password, role_id);
        res.status(201).end();
    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
})

router.post('/signin', async (req, res) => {
    const {
        username,
        password
    } = req.body;

    try {
        const fieldsToBeValidated = {
            username: {
                value: username,
                type: 'ascii'
            },
            password: {
                value: password,
                type: 'ascii'
            }
        };

        validateFields(fieldsToBeValidated);

        let token = await UsersService.authenticate(username, password);

        res.status(200).json(token);
    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }

})

// ruta pt verificarea datelor
router.get('/', async (req, res) => {
    res.json(await UsersService.getUsers());
});


module.exports = router;