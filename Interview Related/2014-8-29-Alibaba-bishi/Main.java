

create table User (
	id varchar(20) primary key, //主键
	point int //个人积分
	
	create hash_index in id //给id创建哈希索引
)

create table Order (
	id longint primary key,
	user_id varchar(20) foreign key, //谁下的单
	order_time longint,
)


interface User {
	String getId(); //
	int getPoint(); //获得积分
}

interface Order {
	
	String getUserId();
	
}

interface UserDao {
	User getUserById(String id); 
	void updateUserPoint(String id, int newPoint);
}

interface OrderDao {
	void storeOrderIntoDB(Order order);
}


interface UserService {
	User getUserById(String id);
	void updateUserPoint(String id, int newPoint);
}

interface OrderService {
	Order createOrder(String userId);
	void storeOrderIntoDB(Order order);
}

class TiaoMaoBoxExchangeModule{
	
	static int total_number = 500000;//天猫墨盒总数
	
	UserService userService;
	OrderService orderService;
	
	@inject from outside
	public TiaoMaoBoxExchangeModule(
			UserService userService,
			OrderService orderService) {
		this.userService = userService;
		this.orderService = orderService;
	}
	
	boolean tryIt(String userId) { //尝试抢天猫墨盒
		Order order = orderService.createOrder(userId);
		User user = userService.getUserById(userId);
		if (user.getPoint() < 99) {
			return false;
		}
		if (total_number <= 0) {
			return false;
		}
		userService.updateUserPoint(userId, user.getPoint() - 99);
		//this operate need synchronized
		total_number --;
		orderService.storeOrderIntoDB(order);
		return true;
	} 
}


public class Main {
	public static enum Fruit {
		APPLE,
		PEAR
	}
	
	public static void main(String[] args) {
		Fruit fruit = Fruit.APPLE;
		Fruit.
		System.out.println(fruit.toString());
	} 
}
