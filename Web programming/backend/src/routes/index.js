'use strict';
var express = require('express');
var router = express.Router();

const UsersController = require('../UsersAPI/controllers.js');
const EndpointController = require('../EndpointAPI/controllers.js');

router.use('/users', UsersController);
router.use('/endpoint', EndpointController);

module.exports = router;
