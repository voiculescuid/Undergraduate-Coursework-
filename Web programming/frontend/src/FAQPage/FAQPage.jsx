import React from 'react';

import { FAQ } from '../_components'

import './FAQPage.module'

class FAQPage extends React.Component {
    render() {
        return (
            <div className="d-flex justify-content-center col-lg">
                <FAQ/>
            </div>
        );
    }
}

export { FAQPage };