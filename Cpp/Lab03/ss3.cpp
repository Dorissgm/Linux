#include <bits/stdc++.h>
using namespace std;
using chrono::system_clock;

// ------------------ Lớp trừu tượng Vehicle (Abstraction) ------------------
class Vehicle {
protected:
    string plate;
public:
    Vehicle(const string& p) : plate(p) {}
    virtual ~Vehicle() = default;
    string getPlate() const { return plate; } // encapsulated getter

    // phương thức ảo để lấy giá cơ sở (polymorphism)
    virtual int basePrice() const = 0;
    virtual string typeName() const = 0;
};

// Xe máy
class Motorbike : public Vehicle {
public:
    Motorbike(const string& p) : Vehicle(p) {}
    int basePrice() const override { return 5000; } // 5k
    string typeName() const override { return "Xe may"; }
};

// Ô tô
class Car : public Vehicle {
public:
    Car(const string& p) : Vehicle(p) {}
    int basePrice() const override { return 10000; } // 10k
    string typeName() const override { return "O to"; }
};

// ------------------ Person (Base) -> Staff, Admin (Inheritance) ------------------
class Person {
protected:
    string name;
    string role;
public:
    Person(const string& n, const string& r) : name(n), role(r) {}
    virtual ~Person() = default;
    string getName() const { return name; }
    string getRole() const { return role; }
};

class Staff : public Person {
public:
    Staff(const string& n) : Person(n, "Staff") {}
    // Staff có thể cấp vé, xử lý thanh toán => thao tác bởi ParkingManager
};

class Admin : public Person {
public:
    Admin(const string& n) : Person(n, "Admin") {}
    // Admin quản lý báo cáo, danh sách staff...
};

// ------------------ Ticket (Encapsulation) ------------------
class Ticket {
private:
    static int nextId;
    int id;
    string customerName;
    unique_ptr<Vehicle> vehicle; // polymorphic ownership
    time_t entryTime;
    time_t exitTime;
    string staffName;
    long long amount; // thành tiền VND
    bool paid;

public:
    Ticket(const string& cust, Vehicle* v, time_t inT, const string& staff)
        : id(nextId++), customerName(cust), vehicle(v), entryTime(inT),
          exitTime(0), staffName(staff), amount(0), paid(false) {}

    int getId() const { return id; }
    string getCustomerName() const { return customerName; }
    string getVehicleType() const { return vehicle->typeName(); }
    string getVehiclePlate() const { return vehicle->getPlate(); }
    string getStaffName() const { return staffName; }

    void setExitTime(time_t t) { exitTime = t; }
    time_t getEntryTime() const { return entryTime; }
    time_t getExitTime() const { return exitTime; }

    double parkingHours() const {
        if (exitTime == 0) return 0.0;
        double diff = difftime(exitTime, entryTime);
        double hours = diff / 3600.0;
        return hours;
    }

    // Tính tiền theo cấp số nhân như quy định, lưu vào amount
    void computeAmount() {
        if (exitTime == 0) {
            amount = 0;
            return;
        }
        double hours = parkingHours();
        int multiplier = 1;
        if (hours <= 5.0) multiplier = 1;
        else if (hours <= 10.0) multiplier = 2;
        else if (hours <= 24.0) multiplier = 4;
        else multiplier = 8;

        amount = (long long)vehicle->basePrice() * multiplier;
        paid = true;
    }

    long long getAmount() const { return amount; }
    bool isPaid() const { return paid; }

    string timeToString(time_t t) const {
        if (t == 0) return string("N/A");
        tm *lt = localtime(&t);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", lt);
        return string(buf);
    }

    void printInvoice() const {
        cout << "------- HOA DON (Ticket ID: " << id << ") -------\n";
        cout << "Khach hang: " << customerName << "\n";
        cout << "Loai xe: " << getVehicleType() << " | Bien so: " << getVehiclePlate() << "\n";
        cout << "Thoi gian vao: " << timeToString(entryTime) << "\n";
        cout << "Thoi gian ra : " << timeToString(exitTime) << "\n";
        cout << fixed << setprecision(2);
        cout << "Tong gio dang gui: " << parkingHours() << " h\n";
        cout << "NV thu phi: " << staffName << "\n";
        cout << "Thanh tien: " << amount << " VND\n";
        cout << "----------------------------------------\n";
    }
};

int Ticket::nextId = 1;

// ------------------ ParkingManager ------------------
class ParkingManager {
private:
    vector<shared_ptr<Staff>> staffList;
    vector<shared_ptr<Admin>> adminList;
    vector<Ticket> tickets;

public:
    // thêm staff/admin
    void addStaff(const string& name) {
        staffList.push_back(make_shared<Staff>(name));
    }
    void addAdmin(const string& name) {
        adminList.push_back(make_shared<Admin>(name));
    }

    vector<string> listStaffNames() const {
        vector<string> res;
        for (auto &s: staffList) res.push_back(s->getName());
        return res;
    }

    // Staff cấp vé: tạo ticket (chỉ có entry time)
    int issueTicket(const string& staffName, const string& customerName,
                    const string& vehicleType, const string& plate, time_t entryTime) 
    {
        Vehicle* v = nullptr;
        if (vehicleType == "1") v = new Motorbike(plate);
        else v = new Car(plate);

        Ticket t(customerName, v, entryTime, staffName);
        tickets.push_back(move(t));
        return tickets.back().getId();
    }

    // Khi khách ra: cập nhật exit time, tính tiền
    bool closeTicket(int ticketId, time_t exitTime) {
        for (auto &t : tickets) {
            if (t.getId() == ticketId) {
                t.setExitTime(exitTime);
                t.computeAmount();
                return true;
            }
        }
        return false;
    }

    // In hóa đơn theo ticket ID
    bool printInvoice(int ticketId) {
        for (auto &t : tickets) {
            if (t.getId() == ticketId) {
                t.printInvoice();
                return true;
            }
        }
        return false;
    }

    // Báo cáo ngày: số vé và tổng thu theo loại xe
    void dailyReport() {
        int countBike = 0, countCar = 0;
        long long sumBike = 0, sumCar = 0;
        for (auto &t : tickets) {
            if (!t.isPaid()) continue;
            if (t.getVehicleType() == "Xe may") {
                countBike++;
                sumBike += t.getAmount();
            } else {
                countCar++;
                sumCar += t.getAmount();
            }
        }
        cout << "\n=== BAO CAO TRONG NGAY ===\n";
        cout << "So luong ve xe may: " << countBike << " | Doanh thu: " << sumBike << " VND\n";
        cout << "So luong ve o to: " << countCar << " | Doanh thu: " << sumCar << " VND\n";
        cout << "Tong: " << (countBike + countCar) << " ve | Doanh thu: " << (sumBike + sumCar) << " VND\n";
        cout << "-------------------------\n";
    }

    // Liệt kê tickets (tùy chọn) để quản lý
    void listAllTickets() {
        cout << "\n-- Danh sach tat ca ticket --\n";
        for (auto &t : tickets) {
            cout << "ID: " << t.getId()
                 << " | Khach: " << t.getCustomerName()
                 << " | Loai: " << t.getVehicleType()
                 << " | Bien so: " << t.getVehiclePlate()
                 << " | NV: " << t.getStaffName()
                 << " | Thanh tien: " << t.getAmount()
                 << " | Paid: " << (t.isPaid() ? "Yes" : "No") << "\n";
        }
    }
};

// ------------------ Hỗ trợ nhập thời gian dạng "YYYY-MM-DD HH:MM" ------------------
time_t parseDateTime(const string& s) {
    std::tm tm{};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        return 0;
    }
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    return mktime(&tm);
}

void showMenu() {
    cout << "\n===== Parking Management =====\n";
    cout << "1. Add staff\n";
    cout << "2. Issue ticket (staff)\n";
    cout << "3. Close ticket and print invoice (staff)\n";
    cout << "4. Customer request invoice (by ticket ID)\n";
    cout << "5. Admin: daily report\n";
    cout << "6. List tickets\n";
    cout << "0. Exit\n";
}

// ------------------ Main (CLI) ------------------
int main() {
    ParkingManager mgr;

    // khởi tạo 1 admin & 1 staff mẫu
    mgr.addAdmin("Admin01");
    mgr.addStaff("Staff01");

    while (true) {
        showMenu();
        int choice;
        cout << "Lua chon: ";
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;
        else if (choice == 1) {
            string name;
            cout << "Nhap ten staff: ";
            getline(cin, name);
            mgr.addStaff(name);
            cout << "Da them staff: " << name << "\n";
        }
        else if (choice == 2) {
            // Issue ticket
            cout << "Danh sach staff hien co:\n";
            auto names = mgr.listStaffNames();
            for (size_t i=0;i<names.size();++i) cout << i+1 << ". " << names[i] << "\n";
            cout << "Nhap ten staff cap ve: ";
            string staffName; getline(cin, staffName);
            cout << "Nhap ten khach: ";
            string cust; getline(cin, cust);
            cout << "Chon loai xe (1 = Xe may, 2 = O to): ";
            string vt; getline(cin, vt);
            cout << "Nhap bien so: ";
            string plate; getline(cin, plate);
            cout << "Nhap thoi gian vao (YYYY-MM-DD HH:MM): ";
            string inS; getline(cin, inS);
            time_t inT = parseDateTime(inS);
            if (inT == 0) { cout << "Sai dinh dang thoi gian!\n"; continue; }
            int id = mgr.issueTicket(staffName, cust, vt, plate, inT);
            cout << "Da cap ticket. ID = " << id << "\n";
        }
        else if (choice == 3) {
            cout << "Nhap ticket ID: ";
            int id; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap thoi gian ra (YYYY-MM-DD HH:MM): ";
            string outS; getline(cin, outS);
            time_t outT = parseDateTime(outS);
            if (outT == 0) { cout << "Sai dinh dang thoi gian!\n"; continue; }
            bool ok = mgr.closeTicket(id, outT);
            if (!ok) cout << "Ticket ID khong tim thay!\n";
            else {
                mgr.printInvoice(id);
            }
        }
        else if (choice == 4) {
            cout << "Nhap ticket ID de in hoa don: ";
            int id; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!mgr.printInvoice(id)) cout << "Ticket ID khong tim thay!\n";
        }
        else if (choice == 5) {
            mgr.dailyReport();
        }
        else if (choice == 6) {
            mgr.listAllTickets();
        }
        else cout << "Lua chon khong hop le\n";
    }

    cout << "Thoat chuong trinh.\n";
    return 0;
}
