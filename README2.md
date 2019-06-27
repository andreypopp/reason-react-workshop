# Reason React Todo app workshop

## Prerequisites

* VS Code + reason-vscode [https://reasonml.github.io/docs/en/editor-plugins](https://reasonml.github.io/docs/en/editor-plugins)
* ?

## Setup

* Install bucklescript cli via `npm install -g bs-platform` or `yarn global add bs-platform` [https://reasonml.github.io/docs/en/installation](https://reasonml.github.io/docs/en/installation)
* Create a project folder via `bsb -init reason-react-todo -theme react-hooks` [https://reasonml.github.io/reason-react/docs/en/installation.html](https://reasonml.github.io/reason-react/docs/en/installation.html)
* Go to newly created folder `cd reason-react-todo`
* Install dependencies `npm install` or `yarn`

## Run

* Run `npm start` (`yarn start`) in one terminal tab
* And `npm run server` (`yarn server`) in another tab

## Work

### Optional styling

You can do whatever you want with the styles, but if you aren't feeling like it, you can use Bulma.
To use it include
```html
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bulma/0.7.5/css/bulma.min.css">
<script defer src="https://use.fontawesome.com/releases/v5.3.1/js/all.js"></script>
```
in the `head` section of `src/index.html`.
Of course, you would want more advanced way for usage in production, but let's leave this out of the scope of this workshop.
Take a look at [https://bulma.io/documentation](https://bulma.io/documentation) if you decided to go that way

### The things you would likely want to implement

* Adding a Todo
* Checking Todo as completed
* Unchecking Todo as completed
* Removing a Todo
* Summary of how many is completed and how many is open
* Filtration by status
* Editing a Todo

You can look at classic TodoMVC http://todomvc.com/examples/react/#/
