//求解a*x^2 + b*x + c = 0;
vector <double> equal_solver(double a, double b, double c) {
    vector <double> ret;
    if (fabs(a) < 1e-8) {
        if (fabs(b) < 1e-8) {
            if (fabs(c) < 1e-8)
                return vector<double>(3, 0.0); //无穷多个解
            else
                return vector<double>(); //无解
        } else {
            ret.push_back(-c / b);
        }
    } else {
        double delta = b * b - 4 * a * c;
        if (delta < 0.0)
            return vector<double>(); //无解
        delta = sqrt(delta);
        ret.push_back((-b + delta) / 2.0 / a);
        ret.push_back((-b - delta) / 2.0 / a);
    }
    return ret;
}