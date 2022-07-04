const log4js = require('log4js');
log4js.configure({
  appenders: { 
	cheese: { type: 'file', filename: 'cheese.log' },
	out: { type: 'console' },
  },
  categories: { default: { appenders: ['out'], level: 'trace' } }
});
 
const logger = log4js.getLogger('cheese1');
logger.trace('Entering cheese testing');
logger.debug('Got cheese.');
logger.info('Cheese is Comt��.');
logger.warn('Cheese is quite smelly.');
logger.error('Cheese is too ripe!');
logger.fatal('Cheese was breeding ground for listeria.');