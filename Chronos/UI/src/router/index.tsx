import { BrowserRouter, Routes, Route } from "react-router-dom";

import Dashboard from "../pages/Dashboard";
import Plan from "../pages/Plan";
import Timeline from "../pages/Timeline";
import AppLayout from "../components/layout/AppLayout";

export default function Router() {
    return (
        <BrowserRouter>
            <Routes>
                <Route element={<AppLayout />}>
                    <Route path="/" element={<Dashboard />} />
                    <Route path="/plan" element={<Plan />} />
                    <Route path="/timeline" element={<Timeline />} />
                </Route>
            </Routes>
        </BrowserRouter>
    );
}