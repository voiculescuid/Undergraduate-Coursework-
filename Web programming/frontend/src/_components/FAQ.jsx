import React, { useState } from 'react';
import { ListGroup, ListGroupItem, ListGroupItemHeading, ListGroupItemText, Collapse } from 'reactstrap';

const FAQuest = ({ question, response }) => {
    const [isOpen, setIsOpen] = useState(false);

    const toggle = () => setIsOpen(!isOpen);

    return (
        <div>
            <ListGroupItemHeading onClick={toggle}> {question} </ListGroupItemHeading>
            <Collapse isOpen={isOpen}>
                <ListGroupItemText > {response} </ListGroupItemText>
            </Collapse>
        </div>
    );
}

export const FAQ = () => {
        return (
            <div className="col-lg">
                <ListGroup>
                    <ListGroupItem active tag="a" href="#" action>General questions</ListGroupItem>
                    <ListGroupItem tag="a" action><FAQuest question="What is the porpose of this site?" response="For user is to download the product, for administrator is to verify published files." /></ListGroupItem>
                    <ListGroupItem tag="a" action><FAQuest question="How i can contact the administrator?" response="You can find him at email: voiculescuid@gmail.com." /></ListGroupItem>
                    <ListGroupItem tag="a" action><FAQuest question="How i can download the product?" response="In the navbar you have 'Dashboard' menu, click it and you will be redirected to download page!" /></ListGroupItem>
                    <ListGroupItem tag="a" action><FAQuest question="How reliable is the solution?" response="This application offer anti-ransomware protection for file system." /></ListGroupItem>
                    <ListGroupItem disabled tag="a" href="#" action>For more contact your administrator.</ListGroupItem>
                </ListGroup>

            </div>
        );
}
