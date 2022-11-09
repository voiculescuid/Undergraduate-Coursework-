const express = require('express');
const { validateFields } = require('../utils');
const FilesService = require('./services.js');
const router = express.Router();

router.post('/publish', async (req, res) => {
    const {
        fileName,
        fileHash,
        fileSize
    } = req.body;

    try {

        const fieldsToBeValidated = {
            fileName: {
                value: fileName,
                type: 'ascii'
            },
            fileHash: {
                value: fileHash,
                type: 'ascii'
            },
            fileSize: {
                value: fileSize,
                type: 'int'
            }
        };

        validateFields(fieldsToBeValidated);

        await FilesService.add(fileName, fileHash, fileSize);

        res.status(201).end();
    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
});

router.post('/check', async (req, res, next) => {
    const {
        fileName,
        fileHash,
        fileSize
    } = req.body;

    try {

        const fieldsToBeValidated = {
            fileName: {
                value: fileName,
                type: 'ascii'
            },
            fileHash: {
                value: fileHash,
                type: 'ascii'
            },
            fileSize: {
                value: fileSize,
                type: 'int'
            }
        };

        validateFields(fieldsToBeValidated);

        const file = await FilesService.check(fileName, fileHash, fileSize);

        if (file.length) {
            res.json({ status:"untrust" });
        }
        res.json({ status: "trust" });

    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
});

router.get('/', async (req, res) => {

    try {

        const files = await FilesService.getAll();
        res.json(files);

    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
});

router.delete('/:id', async (req, res) => {
    const {
        id
    } = req.params;

    try {

        await FilesService.deleteById(id);
        res.status(202).end();

    } catch (err) {
        console.log(err.message);
        res.status(400).end();
    }
});

module.exports = router;