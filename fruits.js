
function Fruit(){}
Fruit.prototype = {
    weight: 0,
    name: "Fruit",
    getWeight: function(){ return this.weight},
    getName: function(){return this.name},
    CalculateCalories: function(){return 1;}
};

function RedFruit(){}
RedFruit.prototype = Object.create(Fruit.prototype);

function TinyFruit(){}
TinyFruit.prototype = {
    __proto__: Fruit.prototype,
    CalculateCalories: function () {
        return `this.weight * 1.5;`
    }
};

function Berry(){}
Berry.prototype = {
    __proto__: TinyFruit.prototype,
    name: "Berry"
};

function BlackBerry(){}
BlackBerry.prototype = {
    __proto__: Berry.prototype,
    name: "BlackBerry"
};

function BlueBerry(){}
BlueBerry.prototype = {
    __proto__: Berry.prototype,
    name: "BlueBerry"
};

function Cherries(){}
Cherries.prototype = {
    __proto__: RedFruit.prototype,
    name: "Cherries",
    CalculateCalories: function () {
        return this.weight * 3.77;
    }
};

var Node = {
    fruit: '',
    left: null,
    right: null,
    getfruit: function(){return this.fruit;},
    getleft: function(){return this.left;},
    getright: function(){return this.right;},
}

var BST = {
    root: null,
    size: 0,
    getRoot: function(){return this.root;},
    getsize: function(){return this.size;},

    // a method that inserts a fruit node
    insert: function(fruit){
        var node = Object.create(Node);
        node.fruit = fruit;
        if(this.root == null) {
            this.root = node;
            this.size++;
            return;
        }
        prev = null;
        temp = this.root;
        while ( temp != null){
            if( temp.fruit.weight > fruit.weight ){
                prev = temp;
                temp = temp.left;
            }
            else if (temp.fruit.weight < fruit.weight){
                prev = temp;
                temp = temp.right;
            }
        }
        if(prev.fruit.weight > fruit.weight)
            prev.left = node;
        else prev.right = node;
        this.size++;
    },
    
    // a method that prints the in-order traversal of the tree.
    Iterate: function(){
        this.IterateRec(this.print,this.root);
    },

    // Higher order functions apllication
    // a recursive iteration function 
    // is used for iterate and print or for iterate to filter by type
    IterateRec: function(myFun , node ,type){
        if (node != null) {
            this.IterateRec(myFun , node.left , type);
            myFun(node.fruit , type);
            this.IterateRec(myFun , node.right , type);
        }
    },

    // a method to print the node
    print: function(fruit){
        console.log(fruit.getName() +" "+ fruit.getWeight());
    },

    // a method that prints the nodes of a given fruit type ordered by. weight.
    filterByType: function(type){
        this.IterateRec(this.checkType,this.root,type);
    },

    // a method that checks the type of the fruit and print this node if this is the type we need
    checkType: function(fruit,type){
        if (fruit.getName() == type){
            console.log(fruit.getName() +" "+ fruit.getWeight());
        }
    },

    // a method that prints the nodes that have weight larger than the given amount ordered by wright
    filterByWeight: function(weight){
        node = this.mySearch(this.root , weight);

    },

    // A function to search a given key in BST
    mySearch: function(node,key){
        // Base Cases: node is null or key is present at node
        if (node==null || node.key==key)
            return node;

        // Key is greater than node's key
        if (node.key < key)
            return mySearch(node.right, key);

        // Key is smaller than node's key
        return mySearch(node.left, key);
    },
    
}




// main
var bst = Object.create(BST);
var f1 = Object.create(BlueBerry.prototype, {weight : {value: 9}});
var f2 = Object.create(BlackBerry.prototype, {weight : {value: 60}});
var f3 = Object.create(Cherries.prototype, {weight : {value: 3}});
var f4 = Object.create(Cherries.prototype, {weight : {value: 24}});
var f5 = Object.create(BlueBerry.prototype, {weight : {value: 15}});

bst.insert(f1);
bst.insert(f2);
bst.insert(f3);
bst.insert(f4);
bst.insert(f5);

bst.Iterate();
console.log("==========");
bst.filterByType("BlueBerry");

