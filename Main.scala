package Home
abstract class Fruit(){
  var weight:Int
  var name:String="Fruit"
  def getWeight=weight
  def getName=name
  def setName(name:String){this.name=name}
  def setWeight(weight:Int){this.weight=weight}
  def CalculateCalories()
}
abstract class tinyfruit ()extends Fruit{
   def CalculateCalories={
    this.weight * 1.5}
}
abstract class Berry()extends Fruit {
  this.setName("Berry")
  def CalculateCalories={
    this.weight * 3.5}
}
class BlackBerry(var weight :Int)extends Berry {
  this.setName("BlackBerry")
}
class BlueBerry(var weight :Int)extends Berry {
  this.setName("BlueBerry")
}
class Cherries(var weight :Int)extends tinyfruit {
  this.setName("Cherries")
}
class Node(var fruit: Fruit,var right: Node,var left: Node){
  def this(fruit: Fruit){
    this(fruit,null,null)
  }
  def setFruit(fruit: Fruit)=this.fruit=fruit
  def setRight(right:Node)=this.right=right
  def setLeft(left:Node)=this.left=left
}
class BTS(){
  var root:Node=null
  def changeRoot(newRoot:Node)=this.root=newRoot
  def insert(insertedFruit:Fruit): Unit ={
    if(this.root==null){this.root=new Node(insertedFruit,null,null)}
    else {
      var prev:Node=null
      var current:Node=this.root
      while (current!=null){
        prev=current
        if(insertedFruit.weight>current.fruit.weight){
          current=current.right
        }
        else{
          current=current.left
        }
      }
      if(prev.fruit.weight>insertedFruit.weight)prev.setLeft(new Node(insertedFruit,null,null))
      else {prev.setRight(new Node(insertedFruit,null,null))}
    }
  }
  //function to print depending on Type (it's delegate if it;s a filter by weight or by type or just print)
  def print(node: Node,Type: Any): Unit ={
    Type match {
      case null=> println(f"in order traversal fruit name ${node.fruit.getName} with weight ${node.fruit.weight}")
      case x:String=>filterType(node,Type.toString)
      case x:Int=>{
        var fruit=node.fruit
        if(Type.toString.toInt<fruit.weight){
          println(f"in order traversal fruit name ${node.fruit.getName} with weight ${node.fruit.weight}")}
      }
    }
    //function to filter by type
  def filterType(node: Node,string: String): Unit ={
    var fruit=node.fruit
    if(string.equals("Berry")){fruit match {
      case x: Berry=>println(f"in order traversal fruit name ${node.fruit.getName} with weight ${node.fruit.weight}")
      case _=>
    }}
    if(string.equals("tinyfruit")){fruit match {
      case x: tinyfruit=>println(f"in order traversal fruit name ${node.fruit.getName} with weight ${node.fruit.weight}")
      case _=>
    }}
    else{fruit match {
      case x:Fruit=>if(x.getName.equals(string)){println((f"in order traversal fruit name ${node.fruit.getName} with weight ${node.fruit.weight}"))}
      case _=>
    }}
  }
  }
  //heigher order function to iterate and depend on the passing function it will filter or print
  def iterate(myfun:(Node, Any) => Unit,node: Node,Type: Any): Unit ={
    if(node==null)return
    this.iterate(myfun,node.left,Type)
    myfun(node,Type)
    this.iterate(myfun,node.right,Type)
  }
}
object Main {
  def main(args: Array[String]): Unit = {
   var t=new BTS
    var f1=new Cherries(5)
    var f2=new Cherries(50)
    var f3=new Cherries(70)
    var f5=new BlackBerry(10)
    var f4=new BlackBerry(90)
    t.insert(f1)
    t.insert(f2)
    t.insert(f3)
    t.insert(f4)
    t.insert(f5)
    t.iterate(t.print,t.root,70)


  }
}
