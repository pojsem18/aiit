function [r_peaks, p_wave, t_wave] = ecg_rdetect(ecg_wave, fs, threshold)
%ecg_wave: input signal
%fs:   sampling frequency
%threshold: threshold factor(between 0 y 1)

    global DEBUG_ECG
    % R-Zacken-Detektor mit 2x Ableitung

    n_p_window = 0.15 * fs;
    n_t_window = 0.25 * fs;
    
    n_rs_window = 0.15 * fs;
    n_qr_window = 0.05 * fs;
    
    % remove drift
    if DEBUG_ECG
        disp('remove drift from ecg signal...');
    end
    ecg_wave = ecg_wave - mean(ecg_wave);

    % Bandpass
    if DEBUG_ECG
        disp('bandpass filtering (fu=10Hz, fo=30Hz)...');
    end
    [b, a] = butter(2, [10 30]*2/fs); %define bandpass filter coeff. b and a. (fu=10Hz, fo=30Hz)
    ecg_bp = filtfilt(b, a, ecg_wave);



    % First Differentiation
    if DEBUG_ECG
        disp('Differentiation...');
    end
    ecg_diff1 = [diff(ecg_bp), 0];

    if nargin == 2
        % Lowpass- Filter
        if DEBUG_ECG
            disp('lowpass filtering (fg = 15Hz)...');
        end
        [b, a] = butter(2, 15*2/fs); %define lowpass filter coeff. ba and a (fg = 15Hz)
        ecg_lp = filtfilt(b, a, ecg_diff1);

        % Normalisation and Threshold detect
        if DEBUG_ECG
            disp('Normalisation and Threshold detect...');
        end
        ecg_norm = round(ecg_lp/max(ecg_lp));

        % Second Differantiation
        if DEBUG_ECG
            disp('Differentiation...');
        end
        ecg_diff2 = [diff(ecg_norm), 0];

        %find indices of singal vectors where the signal values are not equal to zero
        if DEBUG_ECG
            disp('find(ecg_diff2)...');
        end
        k = find(ecg_diff2);

        %find start and end points of qrs complex
        %the time between two signals musst be greater than 0.6 sec.
        sep_time = 0.6;
        sep = sep_time * fs;

        ks(1) = k(1);       % var containing all start points
        ke = [];            % var containing all end points
        if DEBUG_ECG
            disp('find start and end points of qrs complex...');
        end
        for index = 1: length(k)-1
            if k(index +1) - k(index) > sep % found end and start point of qrs complex
                ks = [ks, k(index+1)];
                ke = [ke, k(index)];
            end;
        end;
        ke = [ke, k(end)];

        %finds the index (R peak) of the maximum ekg signal values between the start end end points
        if DEBUG_ECG
            disp('finds the index (R peak) of the maximum ekg signal values between the start end end points...');
        end
        n_anz_rpeaks = length(ks);
        r_peaks = zeros(1, n_anz_rpeaks);
        p_value = zeros(1, n_anz_rpeaks);
        t_value = zeros(1, n_anz_rpeaks);
        for index = 1: n_anz_rpeaks
             [r_value, r_index] = max(ecg_wave(ks(index):ke(index)));
             r_index = ks(index) + r_index - 1;
             r_peaks(index) = r_index;
             if nargout >1 
                 p_start = r_index - n_qr_window - n_p_window;
                 p_stop = r_index - n_qr_window;
                 [p_value, p_index] = max(ecg_wave(p_start: p_stop));
                 p_wave(index) = p_start + p_index-1;
             end
             
             if nargout == 3
                 t_start = r_index + n_rs_window;           
                 try,
                    t_stop = r_index + n_rs_window + n_t_window;
                    [t_value, t_index] = max(ecg_wave(t_start: t_stop));

                 catch,
                    [t_value, t_index] = max(ecg_wave(r_index + n_rs_window: end));
                 end

                 t_wave(index) = t_start + t_index -1;
              end
        end;

    elseif nargin==3

        if DEBUG_ECG
            disp('define upper and lower threshold');
        end
        ekg_thres_max = max(ecg_diff1)*threshold;
        ekg_thres_min = min(ecg_diff1)*threshold;

        ecgdiff1_upper_thres = zeros(1, length(ecg_diff1));
        ecgdiff1_lower_thres = zeros(1, length(ecg_diff1));

        if DEBUG_ECG
            disp('find inidices of the signal vektor which were crossing the thresholds');
        end
        ecgdiff1_upper_thres(find(ecg_diff1>ekg_thres_max))=1;
        ecgdiff1_lower_thres(find(ecg_diff1<ekg_thres_min))=-1;


        ecgdiff1_upper_thres = [0, diff(ecgdiff1_upper_thres)];
        ecgindex_upper_thres = find(ecgdiff1_upper_thres>0);
        ecgdiff1_lower_thres = [0, diff(ecgdiff1_lower_thres)];
        ecgindex_lower_thres = find(ecgdiff1_lower_thres<0);

        n_160ms = round(0.16*fs);
        n_sep = round(0.4 *fs);

        n_maxloops_upper = length(ecgindex_upper_thres);
        n_maxloops_lower = length(ecgindex_lower_thres);

        if DEBUG_ECG
            disp('predict vector size of dedected r-peaks');
        end
        r_peaks = zeros(1, round(n_maxloops_upper));

        n_upper_thres = 1;
        n_lower_thres = 1;
        n_anz_rpeaks = 0;

        if DEBUG_ECG
            disp('find r-peaks...');
        end
        while n_upper_thres<=n_maxloops_upper && n_lower_thres <=n_maxloops_lower
            n_diff1start = ecgindex_upper_thres(1, n_upper_thres);
            n_diff1stop = ecgindex_lower_thres(1, n_lower_thres);
            if n_diff1stop < n_diff1start
                n_lower_thres = n_lower_thres + 1;
                continue
            elseif n_diff1stop - n_diff1start > n_sep
                n_upper_thres = n_upper_thres + 1;
                continue
            end

            %find zero crossover...
            n_null = n_diff1start;
            while n_null < n_diff1stop +1
               if ecg_diff1(1,n_null)<=0
                   break
               end
               n_null = n_null +1;
            end

            %zero crossover found.
            if n_null<=n_diff1stop
                b_found_r = 0;
                % checking if interval P1 -> P1 + 160ms is > lower threshold s2
                if n_diff1start + n_160ms < n_diff1stop
                    n_anz_rpeaks = n_anz_rpeaks + 1;
                    r_peaks(n_anz_rpeaks) = n_null;
                    b_found_r = 1;
                % checking if interval P2 -> P2 + 160ms is < upper threshold s1
                elseif n_upper_thres + 1 <= n_maxloops_upper && n_diff1stop + n_160ms < ecgindex_upper_thres(1, n_upper_thres + 1)
                    n_anz_rpeaks = n_anz_rpeaks + 1;
                    r_peaks(n_anz_rpeaks) = n_null;
                    b_found_r = 1;
                    
                % checking if interval P3 -> P3 + 160ms is > lower threshold s1    
                elseif n_upper_thres + 1 <= n_maxloops_upper && n_lower_thres + 1 <= n_maxloops_lower && ecgindex_upper_thres(1, n_upper_thres + 1) + n_160ms < ecgindex_lower_thres(1, n_lower_thres + 1)
                    n_anz_rpeaks = n_anz_rpeaks + 1;
                    r_peaks(n_anz_rpeaks) = n_null;
                    b_found_r = 1;
                end
                if b_found_r>0
                     if nargout >=1
                         p_start = n_null - n_qr_window - n_p_window;
                         p_stop = n_null - n_qr_window;
                         [p_value, p_index] = max(ecg_wave(p_start: p_stop));
                         p_wave(n_anz_rpeaks) = p_start + p_index-1;
                     end
                     if nargout ==3
                         t_start = n_null + n_rs_window;
                         try
                            t_stop = n_null + n_rs_window + n_t_window;
                            [t_value, t_index] = max(ecg_wave(t_start: t_stop));
                         catch
                             [t_value, t_index] = max(ecg_wave(t_start: end));
                         end
                         t_wave(n_anz_rpeaks) = t_start + t_index-1;
                     end
                end
            end
            n_upper_thres = n_upper_thres + 1;
            n_lower_thres = n_lower_thres + 1;
        end
        r_peaks = r_peaks(1, 1:n_anz_rpeaks);
    end;
    
    if DEBUG_ECG
        
        hfig1 = figure('Name','ECG Wave -> R Peak - Dedection','NumberTitle','off');
        hold on;
        n_300ms = fs * 0.6;
        xaxis_time = 0:1/fs:(length(ecg_wave)*1/fs- 1/fs);
        if nargin == 2
            subplot(3,2,1);
        else
            subplot(3,1,1);
        end
        plot(xaxis_time, ecg_bp);
        axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_bp) max(ecg_bp)]);
        xlabel({'Time';'[s]'});
        ylabel({'U';'[mV]'});
        title('bandpass');
        
        if nargin == 2
            subplot(3,2,2);
        else
            subplot(3,1,2);
        end
        plot(xaxis_time, ecg_diff1);
        axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_diff1) max(ecg_diff1)]);
        xlabel({'Time';'[s]'});
        ylabel({'U';'[mV]'});
        title('differantiation 1');

    
        if nargin == 2
            subplot(3,2,3);
            plot(xaxis_time, ecg_lp);
            xlabel({'Time';'[s]'});
            ylabel({'U';'[mV]'});
            axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_lp) max(ecg_lp)]);
            title('lowpass');
        end;
    
        if nargin == 2
            subplot(3,2,4);
            plot(xaxis_time, ecg_norm);
            xlabel({'Time';'[s]'});
            ylabel({'U';'[mV]'});
            axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_norm) max(ecg_norm)]);
            title('normalisation');
        end;
        
        if nargin == 2
            subplot(3,2,5);
            plot(xaxis_time, ecg_diff2);
            xlabel({'Time';'[s]'});
            ylabel({'U';'[mV]'});
            axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_diff2) max(ecg_diff2)]);
            title('differantiation 2');
        end;
        
        if nargin == 3
            subplot(3,1,3);
            plot(xaxis_time, ecg_diff1);
            hold on;
            plot(ecgindex_upper_thres*1/fs, ecg_diff1(1,  ecgindex_upper_thres), '*r');
            plot(ecgindex_lower_thres*1/fs, ecg_diff1(1,  ecgindex_lower_thres), '*g');
            xlabel({'Time';'[s]'});
            ylabel({'U';'[mV]'});
            axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_diff1) max(ecg_diff1)]);
            title('threshold');
        end; 
        if nargin == 2
            hfig2 = figure('Name','2 times Differentation Method - Representation of ecg wave and r-peaks','NumberTitle','off');
        else
            hfig2 = figure('Name','Threshold Methode - Representation of ecg wave and r-peaks','NumberTitle','off');
        end
        
        hold on;
        plot(xaxis_time, ecg_wave);
        plot(r_peaks*1/fs, ecg_wave(1,r_peaks), '*r');
        if nargout >1
            plot(p_wave*1/fs, ecg_wave(1, p_wave), '+g');
        end
        if nargout == 3
            plot(t_wave*1/fs, ecg_wave(1, t_wave), '+g');
        end
        xlabel({'Time';'[s]'});
        ylabel({'U';'[mV]'});
%         axis([0 (r_peaks(1) + n_300ms)*1/fs min(ecg_wave) max(ecg_wave)]);
end

    
