import { BrowserRouter, Routes, Route } from "react-router-dom";

import AppLayout from "../components/layout/AppLayout";
import Dashboard from "../pages/Dashboard";
import Plan from "../pages/Plan";
import Timeline from "../pages/Timeline";
import Settings from "../pages/Settings";
import Analytics from "../pages/Analytics";

export default function Router() {
    return (
        <BrowserRouter>
            <Routes>
                <Route element={<AppLayout />}>
                    <Route path="/" element={<Dashboard />} />
                    <Route path="/plan" element={<Plan />} />
                    <Route path="/timeline" element={<Timeline />} />
                    <Route path="/analytics" element={<Analytics />} />
                    <Route path="/settings" element={<Settings />} />
                </Route>
            </Routes>
        </BrowserRouter>
    );
}